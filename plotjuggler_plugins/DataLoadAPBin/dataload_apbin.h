/**
 * @file
 * @author Pierre Kancir <pierre.kancir.emn@gmail.com>
 *
 * @section DESCRIPTION
 *
 * ArduPilot DataFlash binaries loader for Plotjuggler.
 * This load and decode ArduPilot DataFlash binaries to extract logging information in readable and plotable state.
 * The logic is derived from Dronekit-La software (https://github.com/dronekit/dronekit-la).
 *
 */

#pragma once

#include <QObject>
#include <QtPlugin>
#include "PlotJuggler/dataloader_base.h"
#include "logformat.h"
#include <QMainWindow>
#include "ui_apbinlog.h"
#include "logwidget.h"
#include <QTabWidget>

using namespace PJ;

class DataLoadAPBIN : public DataLoader
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "facontidavide.PlotJuggler3.DataLoader")
  Q_INTERFACES(PJ::DataLoader)

public:
  DataLoadAPBIN();
  virtual const std::vector<const char*>& compatibleFileExtensions() const override;

  bool readDataFromFile(PJ::FileLoadInfo* fileload_info, PlotDataMapRef& destination) override;

  ~DataLoadAPBIN() override;

  virtual const char* name() const override
  {
    return "ArduPilot Bin";
  }

protected:
private:
  // Timeseries is a struct that hold the data of a message type
  // for each timestamps, there is a list of values paired with their labels

   QMainWindow* _window;
   Ui::APBinLog* _ui;

   uint8_t tab_count;


  struct Timeseries
  {
    std::vector<double> timestamps;
    std::vector<std::pair<std::string, std::vector<double>>> data;
  };

  std::vector<const char*> _extensions;

  static constexpr uint16_t MAX_FORMATS = 256;
  struct log_Format formats[MAX_FORMATS] = {};

  // fill the Timeseries for a message according to the message format
  void handle_message_received(const struct log_Format& format, const uint8_t* msg,
                               std::map<std::string, Timeseries>& _timeseries_map);

  void handle_log_text(const struct log_Format& format, const uint8_t* msg, QTextEdit* current_text);

  void on_renameCurrentTab();

  // create the Timeseries structure for a message time and add it the the map
  static Timeseries createTimeseries(const struct log_Format& format);

};
