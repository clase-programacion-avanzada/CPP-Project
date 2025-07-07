#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Buffer size constants
const int kOneByteNumberBufferSize = 4;
const int kFourByteNumberBufferSize = 11;
const int kPatientgIdBufferSize = 11;
const int kTimestampBufferSize = 24;
const int kNumberOfReadingsBufferSize = 12;
const int kReadingBufferSize = 20;

// Function declarations
int GenerateBinaryFile(const char* text_file_name, const char* binary_file_name);
void ReadAndWriteUciId(fstream& text_file, fstream& binary_file);
int ReadAndWriteNumberOfMachines(fstream& text_file, fstream& binary_file);
void ProcessMachine(fstream& text_file, fstream& binary_file);
void ProcessMeasurement(fstream& text_file, fstream& binary_file);
void ProcessReading(fstream& text_file, fstream& binary_file);
char ReadSingleByteNumber(fstream& text_file, const char* description);
unsigned int ReadFourByteNumber(fstream& text_file);
void WriteStringToBinary(fstream& binary_file, const char* str, int size);


int main() {
    int result_tiny = GenerateBinaryFile("data/generate binary file/patient_readings_simulation_tiny.txt", 
        "patient_readings_simulation_tiny.bsf");
    int result_small = GenerateBinaryFile("data/generate binary file/patient_readings_simulation_small.txt", 
        "patient_readings_simulation_small.bsf");
    int result = GenerateBinaryFile("data/generate binary file/patient_readings_simulation.txt", 
        "patient_readings_simulation.bsf");

    return result_small || result_tiny || result; // Return 0 if all files were generated successfully, otherwise return 1
}


int GenerateBinaryFile(const char* text_file_name, const char* binary_file_name) {
    fstream text_file(text_file_name, ios::in);
    if (text_file.fail()) {
        cerr << "Error opening file: " << text_file_name << endl;
        return 1;
    }

    fstream binary_file(binary_file_name, ios::out | ios::binary);
    if (binary_file.fail()) {
        cerr << "Error creating binary file: " << binary_file_name << endl;
        return 1;
    }

    cout << "Generating binary file from " << text_file_name << " to " << binary_file_name << endl;
    cout << "=========================================================" << endl;

    // Process UCI ID
    ReadAndWriteUciId(text_file, binary_file);

    int number_of_machines = ReadAndWriteNumberOfMachines(text_file, binary_file);

    for (int i = 0; i < number_of_machines; i++) {
        ProcessMachine(text_file, binary_file);
    }

    text_file.close();
    binary_file.close();
    cout << "Binary file generated successfully!" << endl << endl;
    return 0;
}


// Utility function to read a single byte number from text file
char ReadSingleByteNumber(fstream& text_file, const char* description) {
    char* buffer = new char[kOneByteNumberBufferSize];
    text_file.getline(buffer, kOneByteNumberBufferSize);
    int value = atoi(buffer);
    cout << description << ": " << value << endl;
    
    char result = static_cast<char>(value);
    delete[] buffer;
    return result;
}

// Utility function to read a four byte number from text file
unsigned int ReadFourByteNumber(fstream& text_file) {
    char* buffer = new char[kFourByteNumberBufferSize];
    text_file.getline(buffer, kFourByteNumberBufferSize);
    unsigned int value = static_cast<unsigned int>(atoi(buffer));
    
    delete[] buffer;
    return value;
}

// Utility function to write string to binary file
void WriteStringToBinary(fstream& binary_file, const char* str, int size) {
    binary_file.write(str, size);
}

// Read and write UCI ID
void ReadAndWriteUciId(fstream& text_file, fstream& binary_file) {
    char uci_id = ReadSingleByteNumber(text_file, "UCI ID");
    binary_file.write(&uci_id, sizeof(uci_id));
}

// Read and write number of machines
int ReadAndWriteNumberOfMachines(fstream& text_file, fstream& binary_file) {
    char number_of_machines = ReadSingleByteNumber(text_file, "Number of machines");
    binary_file.write(&number_of_machines, sizeof(number_of_machines));
    return static_cast<int>(number_of_machines);
}

// Process a single machine
void ProcessMachine(fstream& text_file, fstream& binary_file) {
    // Read machine ID
    char machine_id = ReadSingleByteNumber(text_file, "Machine ID");
    binary_file.write(&machine_id, sizeof(machine_id));

    // Read number of measurements
    unsigned int number_of_measurements = ReadFourByteNumber(text_file);
    binary_file.write(reinterpret_cast<const char*>(&number_of_measurements), sizeof(number_of_measurements));

    cout << "Processing machine ID: " << static_cast<int>(machine_id) 
         << " with " << number_of_measurements << " measurements." << endl;
    // Process each measurement
    for (unsigned int j = 0; j < number_of_measurements; j++) {
        ProcessMeasurement(text_file, binary_file);
    }
}

// Process a single measurement
void ProcessMeasurement(fstream& text_file, fstream& binary_file) {
    // Read patient ID
    char* patient_id = new char[kPatientgIdBufferSize];
    text_file.getline(patient_id, kPatientgIdBufferSize);
    WriteStringToBinary(binary_file, patient_id, kPatientgIdBufferSize);
    delete[] patient_id;

    // Read timestamp
    char* timestamp = new char[kTimestampBufferSize];
    text_file.getline(timestamp, kTimestampBufferSize);
    WriteStringToBinary(binary_file, timestamp, kTimestampBufferSize);
    delete[] timestamp;

    // Read number of readings
    unsigned int number_of_readings = ReadFourByteNumber(text_file);
    binary_file.write(reinterpret_cast<const char*>(&number_of_readings), sizeof(number_of_readings));

    // Process each reading
    for (unsigned int k = 0; k < number_of_readings; k++) {
        ProcessReading(text_file, binary_file);
    }

}

// Process a single reading
void ProcessReading(fstream& text_file, fstream& binary_file) {
    char* reading_buffer = new char[kReadingBufferSize];
    text_file.getline(reading_buffer, kReadingBufferSize);

    // Parse reading type and value
    char* reading_type = strtok(reading_buffer, " ");
    char* reading_value = strtok(nullptr, " ");

    // Write reading type (single character)
    binary_file.write(reading_type, 1);

    // Process reading value based on type
    if (strcmp(reading_type, "T") == 0 || 
        strcmp(reading_type, "O") == 0 || 
        strcmp(reading_type, "ECG") == 0) {

        double value = atof(reading_value);
        binary_file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    } 
    else if (strcmp(reading_type, "P") == 0) {
        // Pressure readings are stored as two unsigned integers
        char* systolic_str = strtok(reading_value, "-");
        char* diastolic_str = strtok(nullptr, "-");
        
        unsigned int systolic = static_cast<unsigned int>(atoi(systolic_str));
        unsigned int diastolic = static_cast<unsigned int>(atoi(diastolic_str));
        
        binary_file.write(reinterpret_cast<const char*>(&systolic), sizeof(systolic));
        binary_file.write(reinterpret_cast<const char*>(&diastolic), sizeof(diastolic));
    }

    delete[] reading_buffer;
}
