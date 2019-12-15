#include "headers/crow_all.h"
#include "spdlog/spdlog.h"
#include "headers/dbConnector.h"
#include <bsoncxx/json.hpp>

using namespace crow;




int main()
{
    SimpleApp app;
    mongocxx::instance instance{};


    CROW_ROUTE(app, "/create").methods("POST"_method, "PUT"_method)
            ([](const request &req){
                auto db = dbConnector("test", "testicles");
                if (req.method == "POST"_method) {
                    auto x = json::load(req.body);
                    if (!x) {
                        return response(400);
                    }
                    spdlog::info(req.body);
                    db.insertDB(req.body);
                    return response(200, json::dump(x));
                }
                else if (req.method == "PUT"_method) {
                    auto x = json::load(req.body);
                    if (!x) {
                        return response(400);
                    }
                    spdlog::info(req.body);
                    return response(200);
                }
                else {
                    return response(400);
                }
            });

    CROW_ROUTE(app, "/delete").methods("POST"_method)
            ([](const request &req){
                if (req.method == "POST"_method) {
                    auto x = json::load(req.body);
                    if (!x) {
                        return response(400);
                    }
                    spdlog::info(req.body);
                    json::wvalue res;
                    res["deleted"] = true;
                    return response(res);
                }
            });

    CROW_ROUTE(app, "/read/<string>/<string>").methods("POST"_method)
            ([](const request &req, std::string database, std::string collection){
                dbConnector db = dbConnector(database, collection);
                auto filter = req.body;
                json::wvalue mongoResponse;
                std::vector<std::string> jsonArray = db.queryDB(filter);
                std::vector<crow::json::rvalue> outputArray;
                for (auto jsonVal : jsonArray) {
                    outputArray.push_back(json::load(jsonVal));
                }
                mongoResponse["res"] = jsonArray;

                return response(mongoResponse);
            });

    app.port(3000).multithreaded().run();
}
