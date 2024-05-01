#include "training.hpp"
#include "./ui_Training.h"
#include "config_parser.hpp"
#include <QMessageBox>
#include <iomanip>

Training::Training(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Training)
    , configParser("C:\\Users\\natel\\Senior Project\\TRAINING\\larasynth.conf") //Have to use the exact file directory to pull from that file


{
    ui->setupUi(this);
    // Connect the accept and reject slots of the QDialogButtonBox
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Training::on_button_accepted);//OK button
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &Training::on_button_rejected);//cancel button

    // Connect the valueChanged signal of the spinBox to a custom slot
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_updateRate_changed);
    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_blockCounts_changed);
    connect(ui->doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_learningRate_changed);
    connect(ui->doubleSpinBox_4, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_momentum_changed);
    connect(ui->doubleSpinBox_5, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_meanPadding_changed);
    connect(ui->doubleSpinBox_6, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_paddingStdDev_changed);
    connect(ui->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_exampleRepetitions_changed);
    connect(ui->spinBox_4, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_validationExampleRepetitions_changed);
    connect(ui->doubleSpinBox_8, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_tempoAjustment_changed);
    connect(ui->doubleSpinBox_7, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_tempoJitter_changed);
    connect(ui->doubleSpinBox_9, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_resetProb_changed);
    connect(ui->spinBox_7, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_trainingFailures_changed);
    connect(ui->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_squaredTrainingFailureTolerance_changed);
    connect(ui->spinBox_8, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_epochCount_changed);
    connect(ui->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), this, &::Training::on_epochMaxCount_changed);
    connect(ui->doubleSpinBox_10, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &::Training::on_mseThreshold_changed);
    loadConfigParameters();
}

Training::~Training()
{
    delete ui;
}

void Training::on_button_accepted() {
    // can perform any actions here before closing the window
    // For example, save settings or perform validation
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to make these changes?",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Close the window
        save_to_file();
        this->close();
    }


}

void Training::on_button_rejected() {
    // You can perform any actions here before closing the window
    // For example, prompt the user for confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to close?",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Close the window
        this->close();
    }
    // Otherwise, do nothing to keep the window open

}

void Training::loadConfigParameters(){
    //MIDI
    larasynth::ConfigParameters midiParams = configParser.get_section_params("midi");
    larasynth::ConfigParameter midiControllersParam = midiParams.get_param_by_name("controllers");
    std::vector<int> ListOfControllers = midiControllersParam.get_int_list();//Get the int value list from the list of MIDI params
    for ( int value : ListOfControllers){
        std::cout << value << std::endl;
    }

    larasynth::ConfigParameter midiControllersDefaultParam = midiParams.get_param_by_name("controller_defaults");
    std::vector<int> ControllerDefaults = midiControllersDefaultParam.get_int_list();//Get the int value list from list of controller default
    for ( int value : ControllerDefaults){// Iterate over the list of Controller Defaults
        std::cout << value << std::endl;// Print each feature followed by a newline
    }

    //Representation
    larasynth::ConfigParameters representationParams = configParser.get_section_params("representation");
    larasynth::ConfigParameter representationControllerOutputCounts = representationParams.get_param_by_name("controller_output_counts");
    std::vector<int> ControllerOutputCounts = representationControllerOutputCounts.get_int_list();//Get the int value list from list of controller output counts
    for ( int value : ControllerOutputCounts){// Iterate over the list of Controller Output Counts
        std::cout << value << std::endl;
    }

    larasynth::ConfigParameter representationUpdateRate = representationParams.get_param_by_name("update_rate");
    int UpdateRate = representationUpdateRate.get_int_value();//Get the int value from update_rate
    //std::cout << UpdateRate << std::endl;
    ui->spinBox->setValue(UpdateRate); // Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter representationInputFeatures = representationParams.get_param_by_name("input_features");
    std::vector<std::string>InputFeatures = representationInputFeatures.get_string_list();
    for(const std::string& feature : InputFeatures) { // Iterate over the list of features
        std::cout << feature << std::endl; // Print each feature followed by a newline
    }

    //LSTM
    larasynth::ConfigParameters lstmParams = configParser.get_section_params("lstm");
    larasynth::ConfigParameter lstmBlockCounts = lstmParams.get_param_by_name("block_counts");
    int BlockCounts =  lstmBlockCounts.get_int_value();//Get the int value from block_counts
    //std::cout << BlockCounts << std::endl;
    ui->spinBox_2->setValue(BlockCounts);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter lstmLearningRate= lstmParams.get_param_by_name("learning_rate");
    double LearningRate =  lstmLearningRate.get_real_value();//Get the double value from learning_rate
    //std::cout << LearningRate << std::endl;
    ui->doubleSpinBox_3->setValue(LearningRate); // Set the 0value within the spinBox as the value found in the config file

    larasynth::ConfigParameter lstmMomentum= lstmParams.get_param_by_name("momentum");
    double Momentum =  lstmMomentum.get_real_value();//Get the double value from momentum
    //std::cout << Momentum << std::endl;
    ui->doubleSpinBox_4->setValue(Momentum);// Set the value within the spinBox as the value found in the config file

    //TRAINING
    larasynth::ConfigParameters trainingParams = configParser.get_section_params("training");
    larasynth::ConfigParameter trainingMeanPadding= trainingParams.get_param_by_name("mean_padding");
    double MeanPadding =  trainingMeanPadding.get_real_value();//Get the double value from mean_padding
    //std::cout << MeanPadding << std::endl;
    ui->doubleSpinBox_5->setValue(MeanPadding);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingPaddingStdDev = trainingParams.get_param_by_name("padding_stddev");
    double PaddingStdDev =  trainingPaddingStdDev.get_real_value();//Get the double value from padding_stddev
    //std::cout << PaddingStdDev << std::endl;
    ui->doubleSpinBox_6->setValue(PaddingStdDev);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingExampleRepetitions = trainingParams.get_param_by_name("example_repetitions");
    int ExampleRepetitions = trainingExampleRepetitions.get_int_value();//Get the int value from example_repetitions
    //std::cout << ExampleRepetitions << std::endl;
    ui->spinBox_3->setValue(ExampleRepetitions);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingValidationExampleRepetitions = trainingParams.get_param_by_name("validation_example_repetitions");
    int ValidationExampleRepetitions = trainingValidationExampleRepetitions.get_int_value(); //Get the int value from example_repetitions
    //std::cout << ValidationExampleRepetitions << std::endl;
    ui->spinBox_4->setValue(ValidationExampleRepetitions);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingTempoAjustment = trainingParams.get_param_by_name("tempo_adjustment_factor");
    double TempoAdjustment = trainingTempoAjustment.get_real_value();//Get the int value from tempo_adjustments_factor
    //std::cout << TempoAdjustment << std::endl;
    ui->doubleSpinBox_8->setValue(TempoAdjustment);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingTempoJitter = trainingParams.get_param_by_name("tempo_jitter_factor");
    double TempoJitter = trainingTempoJitter.get_real_value(); //Get the int value from tempo_jitter_factor
    //std::cout << TempoJitter << std::endl;
    ui->doubleSpinBox_7->setValue(TempoJitter);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingResetProb = trainingParams.get_param_by_name("reset_probability");
    double ResetProb = trainingResetProb.get_real_value();//Get the double value from reset_probability
    //std::cout << ResetProb << std::endl;
    ui->doubleSpinBox_9->setValue(ResetProb);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingFailures = trainingParams.get_param_by_name("consecutive_failures_for_reset");
    int Failures = trainingFailures.get_int_value();//Get the int value from consecutive_failures_for_reset
    //std::cout << Failures << std::endl;
    ui->spinBox_7->setValue(Failures); // Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingSquaredErrorFailureTolerance = trainingParams.get_param_by_name("squared_error_failure_tolerance");
    int SquaredErrorFailureTolerance = trainingSquaredErrorFailureTolerance.get_int_value(); //Get the int value from squared_error_failure_tolerance
    //std::cout << SquaredErrorFailureTolerance << std::endl;
    ui->spinBox_6->setValue(SquaredErrorFailureTolerance);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingEpochCount = trainingParams.get_param_by_name("epoch_count_before_validating");
    int EpochCount= trainingEpochCount.get_int_value();//Get the int value from epoch_count_before_validating
    //std::cout << EpochCount << std::endl;
    ui->spinBox_8->setValue(EpochCount);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingEpochMaxCount = trainingParams.get_param_by_name("max_epoch_count");
    int EpochMaxCount = trainingEpochMaxCount.get_int_value();//Get the int value from max_epoch_count
    //std::cout << EpochMaxCount << std::endl;
    ui->spinBox_5->setValue(EpochMaxCount);// Set the value within the spinBox as the value found in the config file

    larasynth::ConfigParameter trainingMseThreshold = trainingParams.get_param_by_name("mse_threshold");
    double MseThreshold =trainingMseThreshold.get_real_value();//Get the double value from mse_thresold
    //std::cout << MseThreshold << std::endl;
    ui->doubleSpinBox_10->setValue(MseThreshold);// Set the value within the spinBox as the value found in the config file
}


// Define the slot function
void Training::on_updateRate_changed(int newValue) {
    // Assuming representationUpdateRate is a member variable of type ConfigParameter
    larasynth::ConfigParameter representationUpdateRate = configParser.get_section_params("representation").get_param_by_name("update_rate");

    // Update the value of the representationUpdateRate
    representationUpdateRate.set_value(newValue);

}

// Define the slot function
void Training::on_blockCounts_changed(int newValue) {
    // Assuming lstmBlockCounts is a member variable of type ConfigParameter
    larasynth::ConfigParameter lstmBlockCounts = configParser.get_section_params("lstm").get_param_by_name("block_counts");

    // Update the value of the lstmBlockCounts
    lstmBlockCounts.set_value(newValue);

}


void Training::on_learningRate_changed(double newValue) {
    // Assuming lstmLearningRate is a member variable of type ConfigParameter
    larasynth::ConfigParameter lstmLearningRate = configParser.get_section_params("lstm").get_param_by_name("learning_rate");

    // Update the value of the lstmLearningRate
    lstmLearningRate.set_value(newValue);

}

void Training::on_momentum_changed(double newValue) {
    // Assuming lstmMomentum is a member variable of type ConfigParameter
    larasynth::ConfigParameter lstmMomentum = configParser.get_section_params("lstm").get_param_by_name("momentum");

    // Update the value of the lstmMomentum
    lstmMomentum.set_value(newValue);

}

void Training::on_meanPadding_changed(double newValue) {
    // Assuming trainingMeanPadding is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingMeanPadding = configParser.get_section_params("training").get_param_by_name("mean_padding");

    // Update the value of the trainingMeanPadding
    trainingMeanPadding.set_value(newValue);

}

void Training::on_paddingStdDev_changed(double newValue){
    // Assuming trainingStdDev is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingPaddingStdDev = configParser.get_section_params("training").get_param_by_name("padding_stddev");

    // Update the value of the trainingPaddingStdDev
    trainingPaddingStdDev.set_value(newValue);
}

void Training::on_exampleRepetitions_changed(int newValue){
    // Assuming trainingExampleRepetitions is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingExampleRepetitions = configParser.get_section_params("training").get_param_by_name("example_repetitions");

    // Update the value of the trainingexampleRepetitions
    trainingExampleRepetitions.set_value(newValue);
}

void Training::on_validationExampleRepetitions_changed(int newValue){
    // Assuming trainingExampleRepetitions is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingValidationExampleRepetitions = configParser.get_section_params("training").get_param_by_name("example_repetitions");

    // Update the value of the trainingValidationExampleRepetitions
    trainingValidationExampleRepetitions.set_value(newValue);
}

void Training::on_tempoAjustment_changed(double newValue){
    // Assuming trainingTempoAdjustment is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingTempoAdjustment = configParser.get_section_params("training").get_param_by_name("tempo_adjustment_factor");

    // Update the value of the trainingTempoAdjustment
    trainingTempoAdjustment.set_value(newValue);
}

void Training::on_tempoJitter_changed(double newValue){
    // Assuming trainingTempoJitter is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingTempoJitter = configParser.get_section_params("training").get_param_by_name("tempo_jitter_factor");

    // Update the value of the trainingTempoJitter
    trainingTempoJitter.set_value(newValue);
}

void Training::on_resetProb_changed(double newValue){
    // Assuming trainingResetProb is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingResetProb = configParser.get_section_params("training").get_param_by_name("reset_probability");

    // Update the value of the trainingResetProb
    trainingResetProb.set_value(newValue);
}

void Training::on_trainingFailures_changed(int newValue){
    // Assuming trainingFailures is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingFailures = configParser.get_section_params("training").get_param_by_name("consecutive_failures_for_reset");

    // Update the value of the trainingFailures
    trainingFailures.set_value(newValue);
}

void Training::on_squaredTrainingFailureTolerance_changed(int newValue){
    // Assuming trainingsquaredTrainingFailureTolerance is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingsquaredTrainingFailureTolerance = configParser.get_section_params("training").get_param_by_name("squared_error_failure_tolerance");

    // Update the value of the trainingsquaredTrainingFailureTolerance
    trainingsquaredTrainingFailureTolerance.set_value(newValue);
}

void Training::on_epochCount_changed(int newValue){
    //Assuming trainingepochCount is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingepochCount = configParser.get_section_params("training").get_param_by_name("epoch_count_before_validating");

    //Update the value of the trainingepochCount
    trainingepochCount.set_value(newValue);
}

void Training::on_epochMaxCount_changed(int newValue){
    //Assuming trainingepochCount is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingepochMaxCount = configParser.get_section_params("training").get_param_by_name("max_epoch_count");

    //Update the value of the trainingepochCount
    trainingepochMaxCount.set_value(newValue);
}

void Training::on_mseThreshold_changed(double newValue){
    // Assuming trainingResetProb is a member variable of type ConfigParameter
    larasynth::ConfigParameter trainingmseThreshold = configParser.get_section_params("training").get_param_by_name("mse_threshold");

    // Update the value of the trainingResetProb
    trainingmseThreshold.set_value(newValue);
}

void Training::write_double(double value, std::ofstream &file) {
    if (value == static_cast<int>(value)) {
        file << std::fixed << std::setprecision(1) << value;
    }
    else {
        file << value;
    }
}
bool Training::save_to_file() {
    std::string filename = "C:\\Users\\natel\\Senior Project\\TRAINING\\larasynth.conf";
    std::ofstream configFile(filename);
    if (!configFile.is_open()) {
        // Failed to open the file
        return false;
    }

    // Write the content of the configuration file
    configFile << "# Sections are denoted by names in square brackets. Lines that begin with a #" << std::endl;
    configFile << "# are comments and are ignored by larasynth." << std::endl;
    configFile << std::endl;

    // Write each section and its parameters
    configFile << "[midi]" << std::endl;
    configFile << "controllers = 1, 2" << std::endl;
    configFile << "controller_defaults =" << std::endl;
    configFile << "   1, 0," << std::endl;
    configFile << "   2, 127" << std::endl;
    configFile << std::endl;

    configFile << "[representation]" << std::endl;
    configFile << "controller_output_counts =" << std::endl;
    configFile << "   1, 10," << std::endl;
    configFile << "   2, 10" << std::endl;
    configFile << "update_rate = " << ui->spinBox->value() << std::endl;
    configFile << "input_features =" << std::endl;
    configFile << "     \"some note on\"," << std::endl;
    configFile << "     \"note struck\"," << std::endl;
    configFile << "     \"note released\"," << std::endl;
    configFile << "     \"velocity\"," << std::endl;
    configFile << "     \"interval\"" << std::endl;
    configFile << std::endl;

    configFile << "[lstm]" << std::endl;
    configFile << "block_counts = "<< ui->spinBox_2->value() << std::endl;
    configFile << "learning_rate = ";
    write_double(ui->doubleSpinBox_3->value(),configFile);
    configFile << std::endl;
    configFile << "momentum = ";
    write_double(ui->doubleSpinBox_4->value(),configFile);
    configFile << std::endl;
    configFile << std::endl;
    

    configFile << "[training]" << std::endl;
    configFile << "mean_padding = ";
    write_double(ui->doubleSpinBox_5->value(), configFile);
    configFile << std::endl;
    configFile << "padding_stddev = ";
    write_double(ui->doubleSpinBox_6->value(), configFile);
    configFile << std::endl;
    configFile << "example_repetitions = "<< ui->spinBox_3->value() << std::endl;
    configFile << "validation_example_repetitions = " << ui->spinBox_4->value() << std::endl;
    configFile << "tempo_adjustment_factor = ";
    write_double(ui->doubleSpinBox_8->value(),configFile);
    configFile << std::endl;
    configFile << "tempo_jitter_factor = ";
    write_double(ui->doubleSpinBox_7->value(), configFile);
    configFile << std::endl;
    configFile << "reset_probability = ";
    write_double(ui->doubleSpinBox_9->value(),configFile);
    configFile << std::endl;
    configFile << "squared_error_failure_tolerance = " << ui->spinBox_6->value()  << std::endl;
    configFile << "consecutive_failures_for_reset = " << ui->spinBox_7->value() << std::endl;
    configFile << "epoch_count_before_validating = " << ui->spinBox_8->value() << std::endl;
    configFile << "max_epoch_count = " << ui->spinBox_5->value() << std::endl;
    configFile << "mse_threshold = ";
    write_double(ui->doubleSpinBox_10->value(), configFile);
    configFile << std::endl;


    // Close the file
    configFile.close();
    return true;
}




