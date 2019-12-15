//
// Created by ben on 2019-12-13.
//

#ifndef REST_API_DBCONNECTOR_H
#define REST_API_DBCONNECTOR_H
#include <iostream>
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using namespace mongocxx;
using namespace bsoncxx;

class dbConnector {
    std::string dbName;
    std::string collection;
    std::string uri;
public:
    dbConnector(const std::string dbName, const std::string collection);
    std::vector<std::string> queryDB(const std::string& jsonQuery);
    void insertDB(const std::string& jsonInsertion);
    void deleteDB(const std::string& jsonDeletion);
};


#endif //REST_API_DBCONNECTOR_H
