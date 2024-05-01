#ifndef TRAINING_H
#define TRAINING_H

#include <QMainWindow>
#include "config_parser.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Training;
}
QT_END_NAMESPACE

class Training : public QMainWindow
{
    Q_OBJECT

public:
    Training(QWidget *parent = nullptr);
    ~Training();


private slots:
    void on_button_accepted();
    void on_button_rejected();
    void loadConfigParameters();
    void on_updateRate_changed(int newValue);
    void on_blockCounts_changed(int newValue);
    void on_learningRate_changed(double newValue);
    void on_momentum_changed(double newValue);
    void on_meanPadding_changed(double newValue);
    void on_paddingStdDev_changed(double newValue);
    void on_exampleRepetitions_changed(int newValue);
    void on_validationExampleRepetitions_changed(int newValue);
    void on_tempoAjustment_changed(double newValue);
    void on_tempoJitter_changed(double newValue);
    void on_resetProb_changed(double newValue);
    void on_trainingFailures_changed(int newValue);
    void on_squaredTrainingFailureTolerance_changed(int newValue);
    void on_epochCount_changed(int newValue);
    void on_epochMaxCount_changed(int newValue);
    void on_mseThreshold_changed(double newValue);
    void write_double(double value, std::ofstream &file);
    bool save_to_file();


private:
    Ui::Training *ui;
    larasynth::ConfigParser configParser;
};
#endif // TRAINING_H
