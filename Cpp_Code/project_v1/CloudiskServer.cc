#include "CloudiskServer.h"
#include "Hash.h"
#include "Token.h"
#include "unixHeader.h"
#include "wfrest/HttpMsg.h"

#include <functional>
#include <wfrest/json.hpp>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>

#include <iostream>

using namespace wfrest;
using Function = CloudiskServer::Function;
using namespace std;
using namespace protocol;


void CloudiskServer::abc(const wfrest::HttpReq *req, wfrest::HttpResp *resp, const string &path) {
    resp->File(path);
}


void CloudiskServer::start(unsigned short port) {
    if (_httpserver.track( ).start(port) == 0) {
        _httpserver.list_routes( );
        _waitGroup.wait( );
        _httpserver.stop( );
    } else {
        printf("Cloudisk Server Start Failed!\n");
    }
}

void CloudiskServer::loadModules( ) {
    loadStaticResourceModule( );
    loadUserRegisterModule( );
    loadUserLoginModule( );
    loadUserInfoModule( );
    loadFileQueryModule( );
    loadFileUploadModule( );
    loadFileDownloadModule( );
}


void CloudiskServer::loadStaticResourceModule( ) {
    _httpserver.GET("/user/signup", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/view/signup.html");
    });


    _httpserver.GET("/static/view/signin.html", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/view/signin.html");
    });

    _httpserver.GET("/static/view/home.html", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/view/home.html");
    });

    _httpserver.GET("/static/js/auth.js", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/js/auth.js");
    });

    _httpserver.GET("/static/img/avatar.jpeg", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/img/avatar.jpeg");
    });

    _httpserver.GET("/file/upload", [](const HttpReq *, HttpResp *resp) {
        resp->File("static/view/index.html");
    });
    _httpserver.Static("/file/upload_files", "static/view/upload_files");
}

void CloudiskServer::loadUserRegisterModule( ) {
    _httpserver.POST("/user/signup", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series) {
        if (req->content_type( ) == APPLICATION_URLENCODED) {
            // 1. 解析请求, 获取用户名和密码
            auto formKV = req->form_kv( );
            string username = formKV["username"];
            string password = formKV["password"];
            cout << "username:" << username << endl;
            cout << "password:" << password << endl;

            series->set_context((void *)resp);

            // 2. 对密码进行加密
            string salt("12345678"); // 这里应该是随机生成
            string encodedPassword(crypt(password.c_str( ), salt.c_str( )));
            cout << "mi wen:" << encodedPassword << endl;

            // 3. 从数据库MySQL中读取用户信息进行登录验证
            string mysqlurl("mysql://root:@localhost");
            auto mysqlTask = WFTaskFactory::create_mysql_task(
                mysqlurl, 1, std::bind(&Function::Signup_Callback, placeholders::_1));
            string sql("INSERT INTO cloudisk.tbl_user(user_name, user_pwd) VALUES('");
            sql += username + "', '" + encodedPassword + "')";
            cout << "sql:\n"
                 << sql << endl;
            mysqlTask->get_req( )->set_query(sql);
            series->push_back(mysqlTask);
        }
    });
}


void CloudiskServer::loadUserLoginModule( ) {
    _httpserver.POST("/user/signin", [](const HttpReq *req, HttpResp *resp, SeriesWork *series) {
        if (req->content_type( ) == APPLICATION_URLENCODED) {
            // 1. 解析请求, 获取用户名和密码
            auto formKV = req->form_kv( );
            string username = formKV["username"];
            string password = formKV["password"];
            cout << "username:" << username << endl;
            cout << "password:" << password << endl;

            series->set_context((void *)resp);

            // 2. 对密码进行加密
            string salt("12345678"); // 这里应该是随机生成
            string encodedPassword(crypt(password.c_str( ), salt.c_str( )));
            cout << "mi wen:" << encodedPassword << endl;
            // 3. 从数据库MySQL中读取用户信息进行登录验证
            string mysqlurl("mysql://root:@localhost");
            auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, std::bind(&Function::MYSQL_CheckUser_Callback, placeholders::_1, username, salt, encodedPassword));


            string sql("select user_pwd from cloudisk.tbl_user where user_name = '");
            sql += username + "' limit 1";
            cout << "sql:\n"
                 << sql << endl;
            mysqlTask->get_req( )->set_query(sql);
            series->push_back(mysqlTask);
        }
    });
}

void CloudiskServer::loadUserInfoModule( ) {
    _httpserver.GET("/user/info", [](const HttpReq *req, HttpResp *resp, SeriesWork *series) {
        // 1. 解析请求
        string username = req->query("username");
        string tokenStr = req->query("token");
        cout << "username:" << username << endl;
        cout << "token:" << tokenStr << endl;
        series->set_context((void *)resp);

        string mysqlurl("mysql://root:@localhost");
        auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1,
                                                          std::bind(&Function::MYSQL_LoadUserInfo_Callback, placeholders::_1, username));

        string sql("select signup_at from cloudisk.tbl_user where user_name = '");
        sql += username + "'";
        mysqlTask->get_req( )->set_query(sql);
        series->push_back(mysqlTask);
    });
}

void CloudiskServer::loadFileQueryModule( ) {
    _httpserver.POST("/file/query", [](const HttpReq *req, HttpResp *resp, SeriesWork *series) {
        // 1. 解析请求: 查询词
        string username = req->query("username");
        string tokenStr = req->query("token");
        cout << "username:" << username << endl;
        cout << "token:" << tokenStr << endl;
        series->set_context((void *)resp);

        // 2. 解析请求： 消息体
        string limitCnt = req->form_kv( )["limit"];

        string mysqlurl("mysql://root:@localhost");
        auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, &Function::MYSQL_LoadFile_Callback);
        string sql("select file_sha1, file_name, file_size, upload_at, last_update from cloudisk.tbl_user_file where user_name = '");
        sql += username + "' limit " + limitCnt;
        cout << "\nsql:\n"
             << sql << endl;
        mysqlTask->get_req( )->set_query(sql);
        series->push_back(mysqlTask);
    });
}

void CloudiskServer::loadFileUploadModule( ) {
    _httpserver.POST("/file/upload",
                     [](const HttpReq *req, HttpResp *resp, SeriesWork *series) {
                         // 1. 解析请求
                         string username = req->query("username");
                         string tokenStr = req->query("token");
                         cout << "username:" << username << endl;
                         cout << "token:" << tokenStr << endl;
                         // 2. 对token进行验证
                         // 3. 解析请求：消息体
                         if (req->content_type( ) == MULTIPART_FORM_DATA) {
                             auto form = req->form( );
                             string filename = form["file"].first;
                             string content = form["file"].second;
                             // 4. 将数据写入服务器本地
                             mkdir("tmp", 0755);
                             string filepath = "tmp/" + filename;
                             int fd = open(filepath.c_str( ), O_CREAT | O_RDWR, 0664);
                             if (fd < 0) {
                                 perror("open");
                                 return;
                             }
                             write(fd, content.c_str( ), content.size( ));
                             close(fd);
                             resp->String("upload Success");

                             // 5. 生成SHA1值
                             Hash hash(filepath);
                             string filehash = hash.sha1( );
                             cout << "filehash:" << filehash << endl;
                             // 6.将文件相关信息写入数据库MySQL中
                             string mysqlurl("mysql://root:123@localhost");
                             auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, nullptr);
                             string sql("INSERT INTO cloudisk.tbl_user_file(user_name,file_sha1,file_size,file_name)VALUES('");
                             sql += username + "','" + filehash + "', " + std::to_string(content.size( )) + ",'" + filename + "')";
                             cout << "\nsql:\n"
                                  << sql << endl;
                             mysqlTask->get_req( )->set_query(sql);
                             series->push_back(mysqlTask);
                         }
                     });
}


void CloudiskServer::loadFileDownloadModule( ) {
    _httpserver.GET("/file/downloadurl", [](const HttpReq *req, HttpResp *resp) {
        string filename = req->query("filename");
        cout << "filename: " << filename << endl;

        // 将下载业务从服务器中分离出去，之后只需要产生一个下载链接就可以了
        // 这要求我们还需要去部署一个下载服务器
        string downloadURL = "http://localhost:8080/" + filename;
        resp->String(downloadURL);
    });
}


// callback
int Function::MYSQL_CheckResult(WFMySQLTask *mysqltask) {
    int state = mysqltask->get_state( );
    int error = mysqltask->get_error( );
    if (state != WFT_STATE_SUCCESS) {
        printf("%s\n", WFGlobal::get_error_string(state, error));
        return -1;
    }
    // 1. 检测SQL语句是否存在语法错误
    auto mysqlResp = mysqltask->get_resp( );
    if (mysqlResp->get_packet_type( ) == MYSQL_PACKET_ERROR) {
        printf("ERROR %d: %s\n", mysqlResp->get_error_code( ),
               mysqlResp->get_error_msg( ).c_str( ));
        return -1;
    }

    return 0;
}


void Function::Signup_Callback(WFMySQLTask *mysqltask) {
    HttpResp *resp = (HttpResp *)series_of(mysqltask)->get_context( );

    if (MYSQL_CheckResult(mysqltask)) {
        resp->String("Singup/Login Failed");
        return;
    }

    MySQLResultCursor cursor(mysqltask->get_resp( ));
    if (cursor.get_cursor_status( ) == MYSQL_STATUS_OK) {
        // 2. 成功写入数据库了
        printf("Query OK. %llu row affected.\n", cursor.get_affected_rows( ));
        resp->String("SUCCESS");
    } else {
        resp->String("Singup/Login Failed");
    }
}


void Function::MYSQL_CheckUser_Callback(WFMySQLTask *mysqlTask, const std::string &username, const std::string &salt, const std::string &encodedPassword) {
    int ret = MYSQL_CheckResult(mysqlTask);
    HttpResp *resp = (HttpResp *)series_of(mysqlTask)->get_context( );

    if (ret != 0) {
        resp->String("Singup Failed");
        return;
    }

    MySQLResultCursor cursor(mysqlTask->get_resp( ));
    if (cursor.get_cursor_status( ) == MYSQL_STATUS_OK) {
        // 2. 成功写入数据库了
        printf("Query OK. %llu row affected.\n", cursor.get_affected_rows( ));
        resp->String("Login Failed");
    } else if (cursor.get_cursor_status( ) == MYSQL_STATUS_GET_RESULT) {
        // 3. 读取数据
        vector<vector<MySQLCell>> matrix;
        cursor.fetch_all(matrix);
        string M = matrix[0][0].as_string( );
        cout << "M:" << M << endl;
        if (encodedPassword == M) {
            // 3.1登录成功的情况, 生成Token信息
            Token token(username, salt);
            string tokenStr = token.genToken( );
            // 3.2构造一个JSON对象，发送给客户端
            using Json = nlohmann::json;
            Json msg;
            Json data;
            data["Token"] = tokenStr;
            data["Username"] = username;
            data["Location"] = "/static/view/home.html"; // 跳转到用户中心页面
            msg["data"] = data;
            resp->String(msg.dump( )); // 序列化之后，发送给客户端

            // 3.3 将Token保存到数据库中
            //
            auto nextTask = WFTaskFactory::create_mysql_task("mysql://root:@localhost", 1, nullptr);
            string sql("REPLACE INTO cloudisk.tbl_user_token(user_name, user_token)VALUES('");
            sql += username + "', '" + tokenStr + "')";
            nextTask->get_req( )->set_query(sql);
            cout << "token sql:\n"
                 << sql << "\n";
            series_of(mysqlTask)
                ->push_back(nextTask);

        } else {
            // 登录失败的情况
            resp->String("Login Failed");
        }
    }
}


void Function::MYSQL_LoadFile_Callback(WFMySQLTask *mysqltask) {
    int ret = MYSQL_CheckResult(mysqltask);
    HttpResp *resp = (HttpResp *)series_of(mysqltask)->get_context( );
    if (ret != 0) {
        resp->String("Singup Failed");
        return;
    }

    auto mysqlResp = mysqltask->get_resp( );


    MySQLResultCursor cursor(mysqlResp);
    if (cursor.get_cursor_status( ) == MYSQL_STATUS_GET_RESULT) {
        // 读操作,获取用户的
        vector<vector<MySQLCell>> matrix;
        cursor.fetch_all(matrix);
        Json msgArr;
        for (size_t i = 0; i < matrix.size( ); ++i) {
            Json row;
            row["FileHash"] = matrix[i][0].as_string( );
            row["FileName"] = matrix[i][1].as_string( );
            row["FileSize"] = matrix[i][2].as_ulonglong( );
            row["UploadAt"] = matrix[i][3].as_datetime( );
            row["LastUpdated"] = matrix[i][4].as_datetime( );
            msgArr.push_back(row); // 在数组中添加一个元素,使用push_back即可
        }
        resp->String(msgArr.dump( ));
    } else {
        // 没有读取到正确的信息
        resp->String("error");
    }
}


void Function::MYSQL_LoadUserInfo_Callback(WFMySQLTask *mysqltask, const std::string &username) {
    int ret = MYSQL_CheckResult(mysqltask);
    HttpResp *resp = (HttpResp *)series_of(mysqltask)->get_context( );
    if (ret != 0) {
        resp->String("Singup Failed");

        return;
    }

    auto mysqlResp = mysqltask->get_resp( );

    MySQLResultCursor cursor(mysqlResp);
    if (cursor.get_cursor_status( ) == MYSQL_STATUS_GET_RESULT) {
        // 读操作,获取用户的注册时间
        vector<vector<MySQLCell>> matrix;
        cursor.fetch_all(matrix);
        string signupAt = matrix[0][0].as_string( );
        Json msg;
        Json data;
        data["Username"] = username;

        data["SignupAt"] = signupAt;
        msg["data"] = data;
        resp->String(msg.dump( ));
    } else {
        // 没有读取到正确的信息
        resp->String("error");
    }
}
