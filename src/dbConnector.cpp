//
// Created by ben on 2019-12-13.
//

#include <sstream>
#include "../headers/dbConnector.h"
#include "spdlog/spdlog.h"


dbConnector::dbConnector(const std::string dbName, const std::string collection) {
    this->dbName = dbName;
    this->collection = collection;
    std::string user = getenv("MONGO_USERNAME");
    std::string password = getenv("MONGO_PASSWORD");
    std::stringstream fmt;
    fmt << "mongodb+srv://" << user << ":" << password << "@cluster0-y3cup.mongodb.net/test?retryWrites=true&w=majority";
    this->uri = fmt.str();
}

std::vector<std::string> dbConnector::queryDB(const std::string& jsonQuery) {
    client conn{mongocxx::uri{this->uri}};
    database db = conn[this->dbName];
    mongocxx::collection coll = db[this->collection];
    std::vector<std::string> output;
    cursor results = coll.find(bsoncxx::from_json(jsonQuery));
    for (auto result : results) {
        spdlog::info(bsoncxx::to_json(result));
        output.push_back(bsoncxx::to_json(result));
    }
    return output;
}

void dbConnector::insertDB(const std::string& jsonInsertion) {
    client conn{mongocxx::uri{this->uri}};
    database db = conn[this->dbName];
    mongocxx::collection coll = db[this->collection];
    coll.insert_one(bsoncxx::from_json(jsonInsertion));
}

void dbConnector::deleteDB(const std::string &jsonDeletion) {
    client conn{mongocxx::uri {this->uri}};
    database db = conn[this->dbName];
    mongocxx::collection coll = db[this->collection];
    coll.delete_one(bsoncxx::from_json(jsonDeletion));
}

