#include <Arduino.h>
#include <Adafruit_MCP3008.h>

#define SAMPLESIZE 5000

Adafruit_MCP3008 adc;

long long timestamp;

float sampleSet[500] = {0};

class Plant
{
private:
  float sampleSet[500] = {0};
  uint16_t amountOfSamples;
  uint8_t encoder_channel;
  uint16_t plantID;
  
  char plant_name[40]; // the username of the plant to give it a bit of character
  char plant_type[40]; // the longest plant name is "Ornithogalum adseptentrionesvergentulum" with 39 characters including its space
  uint64_t plant_age;
public:
  Plant(uint8_t cencoder_channel, char* cplant_type, char* cplant_name, int cplantID);
  Plant();
  float Gather_Data();
  float* Get_Sample_Set();
  ~Plant();
};

Plant::Plant()
{
  plantID = 0;
}

Plant::Plant(uint8_t cencoder_channel, char* cplant_type, char* cplant_name, int cplant_id)
{
  amountOfSamples = 0;
  encoder_channel = cencoder_channel;
  if (cplant_id == 0)
  {
    throw std::invalid_argument("Received invalid ID, it should be greater than 0");
  }
  
  plantID = cplant_id;

  strcpy(plant_name, cplant_name);
  strcpy(plant_type, cplant_type);

  plant_age = 0;
}

float Plant::Gather_Data()
{
  float total_value = 0;
  for (uint16_t i = 0; i < SAMPLESIZE; i++)
  {
    total_value += adc.readADC(encoder_channel);
  }
  return total_value/SAMPLESIZE;  
}

Plant::~Plant()
{
}

class PlantManager
{
private:
  Plant plants[8];
  int amount_of_plants;
public:
  PlantManager();
  ~PlantManager();
  int AddPlant(Plant plant);
  int RemovePlant(int PlantID);
};

PlantManager::PlantManager()
{
  amount_of_plants = 0;
}

PlantManager::~PlantManager()
{
}

int PlantManager::AddPlant(Plant plant)
{
  plants[amount_of_plants];
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if(adc.begin())
  {
    Serial.println("Error: ADC connection failed");
  }
  
  timestamp = millis();

  plants[0] = Plant(0, "Basil", "Big boy");
  plants[1] = Plant(1, "parsly", "Zeep");
  
}


void loop() {
  
  if (timestamp + 300000 < millis())
  {
    
  }
}
