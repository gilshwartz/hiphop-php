
/*
 * TestExt is mostly deprecated.
 *
 * Please don't add new extension tests here if they are possible to
 * write in php.
 *
 * The tests below still remain in C++ generally because they start
 * temporary servers, which is easier from C++.
 */

RUN_TESTSUITE(TestExtCurl);
RUN_TESTSUITE(TestExtMemcached);
RUN_TESTSUITE(TestExtMysql);
RUN_TESTSUITE(TestExtServer);
