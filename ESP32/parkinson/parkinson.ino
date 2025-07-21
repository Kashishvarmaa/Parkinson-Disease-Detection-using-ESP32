#include <EloquentTinyML.h>
// This file contains the TFLite model generated from the Lenses dataset
#include "parkinson_esp32.h"

// Lenses dataset feature details
// Datal cols = ['MDVP:Fo(Hz)', 'MDVP:Fhi(Hz)',	'MDVP:Flo(Hz)', 'MDVP:Jitter(%)', 'MDVP:Jitter(Abs)',	'MDVP:RAP',	'MDVP:PPQ',	'Jitter:DDP', 'MDVP:Shimmer', 'MDVP:Shimmer(dB)',	'Shimmer:APQ3',	'Shimmer:APQ5', 'MDVP:APQ'	'Shimmer:DDA	NHR	', 'HNR	','RPDE',	'DFA	', 'spread1',	'spread2', 	'D2',	'PPE']

// Output Categories are: 
// yes (1), no (2)

#define NUMBER_OF_INPUTS 22 
#define NUMBER_OF_OUTPUTS 1 
#define TENSOR_ARENA_SIZE 7*1024  // Adjust as needed for model size

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

float fResult[NUMBER_OF_OUTPUTS] = {0};  // Array to store prediction results

void setup() {
    Serial.begin(115200);
    if (ml.begin(parkinson_esp32)) {
        Serial.println("Model loaded and ready for inference");
    } else {
        Serial.println("Failed to load model.");
    }
}

// Function to display prediction output
void displayOutput(float *fResult) {
    Serial.print("Prediction: ");
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        if (isnan(fResult[i])) {
            Serial.print("NaN ");
        } else {
          Serial.print(fResult[i]);
          Serial.print(" ");
        }
    }
    Serial.println();
}

float fRes = NULL;



void loop() {
    // Example input values for classification
    float input1[NUMBER_OF_INPUTS] = {0.53480777f,0.20230054f,0.63318249f,0.03684879f,0.0513834f,0.04094412f,
 0.03965702f,0.04093755f,0.04473252f,0.03779786f,0.05219569f,0.04274084f,
 0.03606708f,0.05218898f,0.00528376f,0.74359912f,0.34372499f,0.76463112f,
 0.27353803f,0.46378025f,0.376406f,0.20170744f,}; //More probability for class 1


    float input2[NUMBER_OF_INPUTS] = {0.64559416f,0.21916776f,0.72895437f,0.02318933f,0.01185771f,0.03179191f,
 0.02465166f,0.0317868f,0.00556874f,0.00328677f,0.0094376f,0.00963365f,
 0.00329275f,0.00956477f,0.00324665f,0.91437048f,0.41035184f,0.66840235f,
 0.05105757f,0.376042f,0.30242835f,0.04962844f,}; 

    float input3[NUMBER_OF_INPUTS] = {0.13044035f, 0.02337691f, 0.1995636f,  0.05972046f, 0.09090909f, 0.04913295f,
  0.05787781f, 0.04912506f, 0.04838415f, 0.03944125f, 0.0575886f,  0.05156038f,
  0.04334176f, 0.0575812f,  0.01161791f, 0.73595871f, 0.2625408f,  0.80426763f,
  0.33979985f, 0.41893976f, 0.20718076f, 0.26844549f}; 


  
    // Predict and display results for input1
    if (ml.predict(input1, fResult)) {
        Serial.println("\nThe output value for input1 is:");
        displayOutput(fResult);
    } else {
        Serial.println("Prediction failed for input1.");
    }

    // Predict and display results for input2
    if (ml.predict(input2, fResult)) {
        Serial.println("\nThe output value for input2 is:");
        displayOutput(fResult);
    } else {
        Serial.println("Prediction failed for input2.");
    }

    // Predict and display results for input3
    if (ml.predict(input3, fResult)) {
        Serial.println("\nThe output value for input3 is:");
        displayOutput(fResult);
    } else {
        Serial.println("Prediction failed for input3.");
    }

    delay(1000); // Delay for 1 seconds
}
