#include <cstdint>   // For fixed-width integers like uint8_t, uint32_t
#include <fstream>   // For fstream
#include <iostream>  // For cout, cerr
#include <sstream>   // For stringstream
#include <string>    // For string

using namespace std;


const int kPatientIdBufferSize = 11;
const int kTimestampBufferSize = 24;


bool GenerateBinaryFile(const string& text_file_name,
                        const string& binary_file_name);
void ProcessMachine(fstream& text_file, fstream& binary_file);
void ProcessMeasurement(fstream& text_file, fstream& binary_file);
void ProcessReading(fstream& text_file, fstream& binary_file);
uint8_t ReadSingleByteNumber(fstream& file, const string& description);
uint32_t ReadFourByteNumber(fstream& file, const string& description);
double ReadLineAsDouble(fstream& file, const string& description);


int main() {

    bool success_tiny = GenerateBinaryFile(
      "data/generate binary file/patient_readings_simulation_tiny.txt",
      "patient_readings_simulation_tiny.bsf");
    bool success_small = GenerateBinaryFile(
        "data/generate binary file/patient_readings_simulation_small.txt",
        "patient_readings_simulation_small.bsf");
    bool success_large = GenerateBinaryFile("data/generate binary file/patient_readings_simulation.txt",
                                            "patient_readings_simulation.bsf");

    // Return 0 on success (both true), 1 on any failure.
    return (success_small && success_large && success_tiny) ? 0 : 1;
}

uint8_t ReadSingleByteNumber(fstream& file, const string& description) {
    string line;
    getline(file, line);
    if (line.empty()) {
        cerr << "Error reading " << description << ": empty line." << endl;
        return 0;
    }

    uint8_t number = static_cast<uint8_t>(stoi(line));

    return number;
}

uint32_t ReadFourByteNumber(fstream& file, const string& description) {
    string line;
    getline(file, line);
    if (line.empty()) {
        cerr << "Error reading " << description << ": empty line." << endl;
        return 0;
    }

    uint32_t number = static_cast<uint32_t>(stoi(line));

    return number;
}

double ReadLineAsDouble(fstream& file, const string& description) {
    string line;

    getline(file, line);
    
    if (line.empty()) {
        cerr << "Error reading " << description << ": empty line." << endl;
        return 0.0;
    }

    return stod(line);    
}


bool GenerateBinaryFile(const string& text_file_name,
                        const string& binary_file_name) {

    fstream text_file(text_file_name, ios::in);
    if (text_file.fail()) {
        cerr << "Error opening file: " << text_file_name << endl;
        return false;
    }

    fstream binary_file(binary_file_name,
                            ios::out | ios::binary);
    if (!binary_file.is_open()) {
        cerr << "Error creating binary file: " << binary_file_name
                << endl;
        return false;
    }

    cout << "Generating binary file from " << text_file_name << " to "
                << binary_file_name << endl;
    cout << "========================================================="
                << endl;

    // Process UCI ID (1 byte).
    uint8_t uci_id = ReadSingleByteNumber(text_file, "UCI ID");

    cout << "UCI ID: " << static_cast<int>(uci_id) << endl;
    binary_file.write(reinterpret_cast<const char*>(&uci_id), sizeof(uci_id));

    // Process Number of Machines (1 byte).
    uint8_t number_of_machines = ReadSingleByteNumber(
      text_file, "Number of machines");
 
    cout << "Number of machines: " << static_cast<int>(number_of_machines)
        << endl;
    binary_file.write(reinterpret_cast<const char*>(&number_of_machines),
        sizeof(number_of_machines));

    for (int i = 0; i < number_of_machines; ++i) {
        ProcessMachine(text_file, binary_file);
    }

    text_file.close();
    binary_file.close();
    cout << "Binary file generated successfully!" << endl << endl;
    return true;
}

void ProcessMachine(fstream& text_file, fstream& binary_file) {
     // Read machine ID (1 byte).
    uint8_t machine_id = ReadSingleByteNumber(text_file, "Machine ID");
  
    binary_file.write(reinterpret_cast<const char*>(&machine_id),
                      sizeof(machine_id));
  

    // Read number of measurements (4 bytes).
    uint32_t number_of_measurements = ReadFourByteNumber(text_file, "Number of measurements");
    
    binary_file.write(reinterpret_cast<const char*>(&number_of_measurements),
                    sizeof(number_of_measurements));
    

    cout << "Processing machine ID: " << static_cast<int>(machine_id)
                << " with " << number_of_measurements << " measurements."
                << endl;

    for (uint32_t j = 0; j < number_of_measurements; ++j) {
        ProcessMeasurement(text_file, binary_file);
    }
}

void ProcessMeasurement(fstream& text_file, fstream& binary_file) {
    // Use string to avoid manual memory management.
    string patient_id;
    if (getline(text_file, patient_id)) {
        patient_id.resize(kPatientIdBufferSize, '\0');
        binary_file.write(patient_id.c_str(), kPatientIdBufferSize);
    }

    string timestamp;
    if (getline(text_file, timestamp)) {
        timestamp.resize(kTimestampBufferSize, '\0');
        binary_file.write(timestamp.c_str(), kTimestampBufferSize);
    }

    uint32_t number_of_readings = ReadFourByteNumber(text_file, "Number of readings");
    binary_file.write(reinterpret_cast<const char*>(&number_of_readings),
                        sizeof(number_of_readings));


    for (uint32_t k = 0; k < number_of_readings; ++k) {
        ProcessReading(text_file, binary_file);
    }
}

void ProcessReading(fstream& text_file, fstream& binary_file) {
    string line;

    getline(text_file, line);
    stringstream line_stream(line);
    string reading_type;
    getline(line_stream, reading_type, ' ');  // Read until space.

    // Write reading type (single character).
   
    binary_file.write(reading_type.c_str(), 1);
    
    if (reading_type == "T" || reading_type == "O" || reading_type == "ECG") {
        string value_str;
        getline(line_stream, value_str);
        double value = stod(value_str);
        binary_file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    } else if (reading_type == "P") {
        string pressure_values;
        getline(line_stream, pressure_values);

        stringstream pressure_stream(pressure_values);

        uint32_t systolic = getline(pressure_stream, pressure_values, '-')
                            ? stoul(pressure_values)
                            : 0;
        uint32_t diastolic = getline(pressure_stream, pressure_values)
                            ? stoul(pressure_values)
                            : 0;

        binary_file.write(reinterpret_cast<const char*>(&systolic),
                        sizeof(systolic));
        binary_file.write(reinterpret_cast<const char*>(&diastolic),
                        sizeof(diastolic));
    }
}