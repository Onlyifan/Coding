#ifndef __WD_CloudiskServer_HPP__
#define __WD_CloudiskServer_HPP__

#include "alibabacloud/oss/client/ClientConfiguration.h"
#include "wfrest/HttpMsg.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include <alibabacloud/oss/OssClient.h>
#include <string>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <SimpleAmqpClient/SimpleAmqpClient.h>


struct OSSInfo {
    std::string EndPoint;
    std::string AccessKeyID;
    std::string AccessKeySecret;
    std::string Bucket;
};


struct RabbitMQInfo {
    std::string RabbitURL ;
    std::string Exchange;
    std::string Queue;
    std::string RoutingKey;
};


class CloudiskServer {
public:
    class Function {
    public:
        static void Signup_Callback(WFMySQLTask *mysqltask);
        static void MYSQL_CheckUser_Callback(WFMySQLTask *mysqltask, const std::string &username, const std::string &salt, const std::string &encodedPassword);
        static void MYSQL_LoadUserInfo_Callback(WFMySQLTask *mysqltask, const std::string &username);
        static void MYSQL_LoadFile_Callback(WFMySQLTask *mysqltask);
        static int MYSQL_CheckResult(WFMySQLTask *mysqltask);
        static void OSS_Upload_Callback(WFMySQLTask *mysqltask, CloudiskServer *server, const std::string &filehash, const std::string &filename);
    };

public:
    CloudiskServer(int cnt, OSSInfo &&ossInfo, RabbitMQInfo &&mqInfo, const AlibabaCloud::OSS::ClientConfiguration &conf);

    ~CloudiskServer( );

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
    OSSInfo _ossInfo;
    RabbitMQInfo _mqInfo;
    AlibabaCloud::OSS::OssClient _client;
    AmqpClient::Channel::ptr_t _channel;
    wfrest::HttpServer _httpserver;
};

#endif
