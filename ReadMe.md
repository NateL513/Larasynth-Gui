#GUI ReadMe File

**Description:**
This GUI (Graphical User Interface) was designed by Nate Leigh for configuring parameters related to a training module. It allows users to adjust various settings such as update rates, block counts, learning rates, momentum, and many more, facilitating the customization of training parameters according to specific requirements.

**Version of Qt Used:**
The GUI was developed using Qt, and the version used for development is Qt 6.6.0.

**Environment:**
To run this GUI, ensure you have the following environment set up:
- Qt 6.6.0 or later installed on your system.
- C++ compiler compatible with Qt.
- Access to the necessary configuration files specified in the code.

**UI File:**
The GUI's user interface was created using Qt Designer, and the .ui file associated with this GUI is named Training.ui.

**Running the GUI:**
To run the GUI, follow these steps:
1. Open Qt Creator: Launch Qt Creator, the integrated development environment (IDE) for Qt.
2. Open the Project: Open the project directory containing the GUI code.
3. Build the Project: Build the project using Qt Creator, ensuring that it compiles successfully without any errors.
4. Run the GUI: Once the project is built, run the GUI by selecting the appropriate target (e.g., Debug or Release) and clicking the "Run" button in Qt Creator.

**Usage:**
**Configuration Loading**: Upon initialization, the GUI automatically loads configuration parameters from the specified file (larasynth.conf) and populates the interface elements accordingly.
**Parameter Adjustment**: Users can modify various parameters using the provided input fields and spin boxes.
**Save Changes**: Clicking the "OK" button prompts a confirmation dialog. Upon confirmation, the changes are saved to the configuration file.
**Cancel Changes**: Clicking the "Cancel" button prompts a confirmation dialog. Upon confirmation, the window closes without saving any changes.

**File Structure:**
- **Training.hpp**: Header file containing class declaration and method prototypes.
- **Training.cpp**: Source file containing class implementation and method definitions.
- **Ui_Training.h**: Header file generated by Qt Designer, containing UI-related code.
- **config_parser.hpp**: Header file containing a class for parsing configuration files.
- **larasynth.conf**: Configuration file containing parameters for the training module.

**Note:**
Ensure that the file paths specified in the code (larasynth.conf) are correctly configured to point to the actual location of the configuration file.

**Future Developers**
Your task is to enhance Larasynth by developing additional Graphical User Interfaces (GUIs) for its various components. Collaborate closely with Nathan Sommers to define a comprehensive design plan that aligns with his vision for the project. Additionally, focus on decoupling the configuration file loading and writing processes from the Qt library to increase flexibility and reduce dependencies.

**Key Objectives**
**1. GUI Development:**
- Identify the areas of Larasynth that require additional GUI interfaces.
- Discuss with Nathan Sommers to understand his requirements and expectations for the new GUIs.
- Design intuitive and user-friendly interfaces that enhance the usability of Larasynth.
- Ensure consistency in design and functionality across all GUI components.
**2. Decoupling Configuration Management:**
- Analyze the current implementation of configuration file handling within Larasynth.
- Work on separating the loading and writing of configuration files from the Qt library.
- Implement a modular and platform-independent solution for configuration management.
- Verify that the decoupling process does not adversely affect the functionality of Larasynth.
