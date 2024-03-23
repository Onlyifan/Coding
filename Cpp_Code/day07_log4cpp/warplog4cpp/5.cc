#include "log4cpp/Appender.hh"
#include <iostream>
#include <log4cpp/Appender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using namespace log4cpp;


class AppenderMode {
  public:
    enum Modes { CONSOLE = 1, FILE = 2, ROLLFILE = 4 };
};


class Mylogger {
  private:
  public:
    void emerg(const char *msg, const char *file = __FILE__,
               const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::EMERG, msg, file, func, line);
    }

    void fatal(const char *msg, const char *file = __FILE__,
               const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::FATAL, msg, file, func, line);
    }

    void alert(const char *msg, const char *file = __FILE__,
               const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::ALERT, msg, file, func, line);
    }
    void crit(const char *msg, const char *file = __FILE__,
              const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::CRIT, msg, file, func, line);
    }
    void error(const char *msg, const char *file = __FILE__,
               const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::ERROR, msg, file, func, line);
    }
    void warn(const char *msg, const char *file = __FILE__,
              const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::WARN, msg, file, func, line);
    }
    void notice(const char *msg, const char *file = __FILE__,
                const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::NOTICE, msg, file, func, line);
    }
    void info(const char *msg, const char *file = __FILE__,
              const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::INFO, msg, file, func, line);
    }
    void debug(const char *msg, const char *file = __FILE__,
               const char *func = __PRETTY_FUNCTION__, int line = __LINE__) {
        handlerLog(Priority::DEBUG, msg, file, func, line);
    }

    static Mylogger *
    getInstance(AppenderMode::Modes mode = AppenderMode::CONSOLE,
                Priority::PriorityLevel level = Priority::INFO,
                const char *subject = "default") {
        if (_pInstance == nullptr) {
            _pInstance = new Mylogger(mode, level, subject);
        }
        return _pInstance;
    }

    static void deleteInstance( ) {
        if (_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void setPriority(Priority::PriorityLevel level) {
        _category.setPriority(level);
    }

    void addAppender(AppenderMode::Modes mode) {
        if ((_mode & mode) != 0) {
            return;
        }
        _mode |= mode;


        switch (mode) {
        case AppenderMode::CONSOLE:
            _category.addAppender(_appToConsole);
            break;
        case AppenderMode::FILE:
            _category.addAppender(_appToFile);
            break;
        case AppenderMode::ROLLFILE:
            _category.addAppender(_appToRollFile);
            break;
        }
    }

    void delAppender(AppenderMode::Modes mode) {
        if ((_mode & mode) == 0) {
            return;
        }
        _mode ^= mode;

        switch (mode) {
        case AppenderMode::CONSOLE:
            _category.removeAppender(_appToConsole);
            break;
        case AppenderMode::FILE:
            _category.removeAppender(_appToFile);
            break;
        case AppenderMode::ROLLFILE:
            _category.removeAppender(_appToRollFile);
            break;
        }
    }

  private:
    void handlerLog(Priority::PriorityLevel level, const char *msg,
                    const char *file, const char *func, int line) {
        std::ostringstream oss;
        oss << "Filename:" << file << " Func:" << func << " Line:" << line
            << " Msg:" << msg;
        _category.log(level, oss.str( ));
    }

    Mylogger(AppenderMode::Modes mode, Priority::PriorityLevel level,
             const char *subject)
        : _mode(0)
        , _category(Category::getInstance(subject))
        , _appToConsole(new OstreamAppender("console", &std::cout))
        , _pattern1(new PatternLayout( ))
        , _appToFile(new FileAppender("file", "single_file.log"))
        , _pattern2(new PatternLayout( ))
        , _appToRollFile(
              new RollingFileAppender("rollfile", "roll_file.log", 200, 4))
        , _pattern3(new PatternLayout( )) {
        const char *patternStr = "%d %c [%p]: %m%n";

        _pattern1->setConversionPattern(patternStr);
        _pattern2->setConversionPattern(patternStr);
        _pattern3->setConversionPattern(patternStr);
        _appToConsole->setLayout(_pattern1);
        _appToFile->setLayout(_pattern2);
        _appToRollFile->setLayout(_pattern3);


        setPriority(level);
        addAppender(mode);
    }

    ~Mylogger( ) {
        // Category::shutdown( );
        cout << "~Mylogger()" << endl;
    }


  private:
    static Mylogger *_pInstance;
    int _mode;
    Category &_category;
    OstreamAppender *_appToConsole;
    PatternLayout *_pattern1;
    FileAppender *_appToFile;
    PatternLayout *_pattern2;
    RollingFileAppender *_appToRollFile;
    PatternLayout *_pattern3;
};
Mylogger *Mylogger::_pInstance = nullptr;

#define EXTRA_LOG __FILE__, __PRETTY_FUNCTION__, __LINE__
#define LOG_STATEMENT(level, msg)                                              \
    Mylogger::getInstance( )->level(msg, EXTRA_LOG)
#define LogEmerg(msg) LOG_STATEMENT(emerg, msg)
#define LogFatal(msg) LOG_STATEMENT(fatal, msg)
#define LogAlert(msg) LOG_STATEMENT(alert, msg)
#define LogCrit(msg) LOG_STATEMENT(crit, msg)
#define LogError(msg) LOG_STATEMENT(error, msg)
#define LogWarn(msg) LOG_STATEMENT(warn, msg)
#define LogNotice(msg) LOG_STATEMENT(notice, msg)
#define LogInfo(msg) LOG_STATEMENT(info, msg)
#define LogDebug(msg) LOG_STATEMENT(debug, msg)


void test0( ) {

    Mylogger *log =
        Mylogger::getInstance(AppenderMode::CONSOLE, Priority::ERROR, "test0");
    // log->addAppender(AppenderMode::FILE);
    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    log->emerg("The log is emerg message");
}

void test1( ) {
    LogEmerg("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}


int main(void) {
    test0( );
    test1( );

    Mylogger::deleteInstance( );
    return 0;
}
