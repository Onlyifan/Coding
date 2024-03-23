#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
// 隐式创建的root, Priority == info, Layout == none


using namespace log4cpp;
using std::cout;


void outputLog( ) {

    PatternLayout *pl1 = new PatternLayout;
    pl1->setConversionPattern("%d [%p] %c: %m%n");
    OstreamAppender *appToConsole = new OstreamAppender("console", &cout);
    appToConsole->setLayout(pl1);

    PatternLayout *pl2 = new PatternLayout;
    pl2->setConversionPattern("%d [%p] %c: %m%n");
    FileAppender *appToFile = new FileAppender("file", "single_file.log");
    appToFile->setLayout(pl2);

    PatternLayout *pl3 = new PatternLayout;
    pl3->setConversionPattern("%d [%p] %c: %m%n");
    RollingFileAppender *appToRollFile =
        new RollingFileAppender("rolling_file", "roll_file.log", 200, 9);
    appToRollFile->setLayout(pl3);

    Category &root = Category::getRoot( );
    root.addAppender(appToConsole);
    root.addAppender(appToFile);
    root.setPriority(Priority::ERROR);

    Category &sub1 = Category::getInstance("sub1");
    sub1.setPriority(Priority::INFO);
    sub1.addAppender(appToRollFile);

    root.emerg("this is an emergency message");
    root.fatal("this is an fatal message");
    root.alert("this is an alert message");
    root.crit("this is a ctitical message");
    root.error("this is a error message");
    root.warn("this is a warning message");
    root.notice("this is a notice message");
    root.info("this is a info message");
    root.debug("this is a debug message");


    sub1.emerg("this is an emergency message");
    sub1.fatal("this is an fatal message");
    sub1.alert("this is an alert message");
    sub1.crit("this is a ctitical message");
    sub1.error("this is a error message");
    sub1.warn("this is a warning message");
    sub1.notice("this is a notice message");
    sub1.info("this is a info message");
    sub1.debug("this is a debug message");

    Category::shutdown( );
}

int main(void) {
    outputLog( );

    return 0;
}
