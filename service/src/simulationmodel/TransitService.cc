#include <chrono>  // NOLINT [build/c++11]
#include <map>

#include "DataManager.h"
#include "OBJParser.h"
#include "SimulationModel.h"
#include "WebServer.h"

//--------------------  Controller ----------------------------
bool stopped = false;
/// A Transit Service that communicates with a web page through web sockets.  It
/// also acts as the controller in the model view controller pattern.
class TransitService : public JsonSession, public IController {
 public:
  TransitService()
      : model(*this, nullptr),
        start(std::chrono::system_clock::now()),
        time(0.0) {}

  /// Handles specific commands from the web server
  void receiveCommand(const std::string& cmd, const JsonObject& data,
                      JsonObject& returnValue) {
    // std::cout << cmd << ": " << data << std::endl;
    if (cmd == "CreateEntity") {
      model.createEntity(data);
    } else if (cmd == "SetGraph") {
      std::string path = data["filePath"];
      model.setGraph(routing::OBJGraphParser(path));
    } else if (cmd == "ScheduleTrip") {
      model.scheduleTrip(data);
    } else if (cmd == "ping") {
      if (data.contains("message"))
        std::cout << std::string(data["message"]) << std::endl;
      returnValue["response"] = data;
    } else if (cmd == "Update") {
      updateEntites.clear();

      std::chrono::time_point<std::chrono::system_clock> end =
          std::chrono::system_clock::now();
      std::chrono::duration<double> diff = end - start;
      double delta = diff.count() - time;
      time += delta;

      double simSpeed = data["simSpeed"];
      delta *= simSpeed;

      if (delta > 0.1) {
        for (float f = 0.0; f < delta; f += 0.01) {
          model.update(0.01);
        }
      } else {
        model.update(delta);
      }

      for (auto& [id, entity] : updateEntites) {
        sendEntity("UpdateEntity", *entity);
      }
    } else if (cmd == "stopSimulation") {
      std::cout << "Stop command administered\n";
      stopped = true;
      model.stop();
    } else if (cmd == "exportData") {
      int result = DataManager::getInstance().exportData();
      if (result == 1) {
        std::string message = "failure";
        model.notify(message);
      } else {
        std::string message = "success";
        model.notify(message);
      }
    }
  }

  void sendEntity(const std::string& event, const IEntity& entity,
                  bool includeDetails = true) {
    // JsonObject details = entity.GetDetails();
    JsonObject details;
    if (includeDetails) {
      details["details"] = entity.getDetails();
    }
    details["id"] = entity.getId();
    Vector3 pos_ = entity.getPosition();
    Vector3 dir_ = entity.getDirection();
    JsonArray pos = {pos_.x, pos_.y, pos_.z};
    JsonArray dir = {dir_.x, dir_.y, dir_.z};
    details["pos"] = pos;
    details["dir"] = dir;
    std::string col_ = entity.getColor();
    if (col_ != "") details["color"] = col_;
    sendEventToView(event, details);
  }

  void addEntity(const IEntity& entity) {
    sendEntity("AddEntity", entity, true);
  }

  void updateEntity(const IEntity& entity) {
    updateEntites[entity.getId()] = &entity;
  }

  void removeEntity(const IEntity& entity) {
    JsonObject details;
    details["id"] = entity.getId();
    updateEntites.erase(entity.getId());
    sendEventToView("RemoveEntity", details);
  }

  /// Allows messages to be passed back to the view
  void sendEventToView(const std::string& event, const JsonObject& details) {
    JsonObject eventData;
    eventData["event"] = event;
    eventData["details"] = details;
    sendMessage(eventData.toString());
  }

 private:
  // Simulation Model
  SimulationModel model;
  // Used for tracking time since last update
  std::chrono::time_point<std::chrono::system_clock> start;
  // The total time the server has been running.
  double time;
  // Current entities to update
  std::map<int, const IEntity*> updateEntites;
};

/// The main program that handles starting the web sockets service.
int main(int argc, char** argv) {
  if (argc > 1) {
    int port = std::atoi(argv[1]);
    std::string webDir = std::string(argv[2]);
    WebServer<TransitService> server(port, webDir);
    while (!stopped) {
      server.service();
    }
  } else {
    std::cout
        << "Usage: ./build/bin/transit_service <port> apps/transit_service/web/"
        << std::endl;
  }

  return 0;
}
