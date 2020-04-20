#include "countMinSketch.h"
#include "count_min_sketch.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <map>
#include <cstdio>
#include <fstream>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

std::string parseDrug(std::string& data)
{
    auto posBegin = data.find_first_of("\t");
    auto posEnd = data.find_first_of("\t", posBegin + 1);

    return data.substr(posBegin + 1, posEnd - posBegin - 1);
}

BOOST_AUTO_TEST_CASE(countMinSketch_ready_solution_withoptimal_parameters_test)
{
    /*https://archive.ics.uci.edu/ml/machine-learning-databases/00462/*/
    std::fstream datasetFile("drugsComTest_raw.tsv");

    if (datasetFile.is_open())
    {
        CountMinSketch cms;
        cms_init_optimal(&cms, 0.1, 0.8); //error rate - 0.1, confindence - 0.8
        std::string data;
        getline(datasetFile, data); //first string means nothing

        while (getline(datasetFile, data))
        {
            auto drug = parseDrug(data);
            cms_add(&cms, drug.c_str());
        }
        datasetFile.close();

        auto res = cms_check(&cms, "Mirtazapine");
        BOOST_CHECK_MESSAGE(res >= 150, "Mirtazapine is underestimated"); //150 is the closest value to truth (according to VS Code search engine)

        char msgbuf[128] = { 0 };

        sprintf(msgbuf, "Mirtazapine's number %d\n", res);
        OutputDebugString(msgbuf);
        memset(msgbuf, 0, sizeof(msgbuf));

        res = cms_check(&cms, "Lexapro");
        BOOST_CHECK_MESSAGE(res >= 250, "Lexapro is underestimated"); //250 is the closest value to truth (according to VS Code search engine)
        sprintf(msgbuf, "Lexapro's number %d\n", res);
        OutputDebugString(msgbuf);

        cms_destroy(&cms);
    }
    else
        OutputDebugStringA("cannot open the file");
}

BOOST_AUTO_TEST_CASE(countMinSketch_ready_solution_test)
{
    /*https://archive.ics.uci.edu/ml/machine-learning-databases/00462/*/
    std::fstream datasetFile("drugsComTest_raw.tsv");
    
    if (datasetFile.is_open())
    {
        CountMinSketch cms;
        cms_init(&cms, 10000, 7);
        std::string data;
        getline(datasetFile, data); //first string means nothing

        while (getline(datasetFile, data))
        {
            auto drug = parseDrug(data);
            cms_add(&cms, drug.c_str());
        }
        datasetFile.close();

        auto res = cms_check(&cms, "Mirtazapine");
        BOOST_CHECK_MESSAGE(res >= 150, "Mirtazapine is underestimated"); //150 is the closest value to truth (according to VS Code search engine)

        char msgbuf[128] = { 0 };

        sprintf(msgbuf, "Mirtazapine's number %d\n", res);
        OutputDebugString(msgbuf);
        memset(msgbuf, 0, sizeof(msgbuf));

        res = cms_check(&cms, "Lexapro");
        BOOST_CHECK_MESSAGE(res >= 250, "Lexapro is underestimated"); //250 is the closest value to truth (according to VS Code search engine)
        sprintf(msgbuf, "Lexapro's number %d\n", res);
        OutputDebugString(msgbuf);

        cms_destroy(&cms);
    }   
    else
        OutputDebugStringA("cannot open the file");
}

BOOST_AUTO_TEST_CASE(countMinSketch_my_solution_test)
{
    /*https://archive.ics.uci.edu/ml/machine-learning-databases/00462/*/
    std::fstream datasetFile("drugsComTest_raw.tsv");

    if (datasetFile.is_open())
    {
        MyCountMinSketch cms(10000, 7);  //same parameters like in previous test    
        std::string data;
        getline(datasetFile, data); //first string means nothing

        while (getline(datasetFile, data))
        {
            auto drug = parseDrug(data);
            cms.add(drug);
        }
        datasetFile.close();

        auto res = cms.check("Mirtazapine");
        BOOST_CHECK_MESSAGE(res >= 181, "Mirtazapine is underestimated"); //value 181 was retrieved from previous test for ready solution

        char msgbuf[128] = { 0 };

        sprintf(msgbuf, "Mirtazapine's number %d\n", res);
        OutputDebugString(msgbuf);
        memset(msgbuf, 0, sizeof(msgbuf));

        res = cms.check("Lexapro");
        BOOST_CHECK_MESSAGE(res >= 298, "Lexapro is underestimated"); //value 298 was retrieved from previous test for ready solution
        sprintf(msgbuf, "Lexapro's number %d\n", res);
        OutputDebugString(msgbuf);
    }
    else
        OutputDebugStringA("cannot open the file");
}
/*Output for 3 tests:
    ready solution: error rate - 0.1, confindence - 0.8
    Mirtazapine's number 3082
    Lexapro's number 2903
    
    ready solution: width - 10000, depth - 7
    Mirtazapine's number 181
    Lexapro's number 298

    my solution: width - 10000, depth - 7
    Mirtazapine's number 208
    Lexapro's number 306
*/
BOOST_AUTO_TEST_SUITE_END()
