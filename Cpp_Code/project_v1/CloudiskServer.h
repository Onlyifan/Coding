#ifndef __WD_CloudiskServer_HPP__
#define __WD_CloudiskServer_HPP__

#include "wfrest/HttpMsg.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>

class CloudiskServer {
public:
    class Function {
    public:
        static void Signup_Callback(WFMySQLTask *mysqltask);
        static void MYSQL_CheckUser_Callback(WFMySQLTask *mysqltask, const std::string &username, const std::string &salt, const std::string &encodedPassword);
        static void MYSQL_LoadUserInfo_Callback(WFMySQLTask *mysqltask, const std::string &username);
        static void MYSQL_LoadFile_Callback(WFMySQLTask *mysqltask);
        static int MYSQL_CheckResult(WFMySQLTask *mysqltask);
    };

public:
    CloudiskServer(int cnt)
        : _waitGroup(cnt) {}

    ~CloudiskServer( ) {}

    void start(unsigned short port);

    void loadModules( );

    static void abc(const wfrest::HttpReq *req, wfrest::HttpResp *resp, const std::string &path);

private:
    // 模块化的思维方式写代码
    void loadStaticResourceModule( );
    void loadUserRegisterModule( );
    void loadUserLoginModule( );
    void loadUserInfoModule( );
    void loadFileQueryModule( );
    void loadFileUploadModule( );
    void loadFileDownloadModule( );


private:
    WFFacilities::WaitGroup _waitGroup;
    wfrest::HttpServer _httpserver;
};

#endif
