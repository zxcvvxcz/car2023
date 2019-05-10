
//solarPanel: airplane, submarine에서 car로 바뀌는 순간부터 충전, 바뀌는 순간 next move 이전 표기에는 충전되기 전 값이 출력
//energy/oxygen 등이 0이 된 동시에 도착: arrival
//successfully moved to next 0km: 출력해도 되고 안 해도 됨
//TC1~10이 공개되면 TC를 파일 위치에서 부르지 말고 미리 코드에 저장
//질문:5/9 자정까지
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::rand;
using std::srand;
#include <ctime>
using std::time;
#include <cstring>
#include <string>
using std::getline;
using std::string;
using std::to_string;
#include <vector>
using std::vector;

#include <stdexcept>
using std::runtime_error;

class EnergyZeroException : public runtime_error
{
public:
    EnergyZeroException() : runtime_error("Energy Failure") {}
};

class OxygenZeroException : public runtime_error
{
public:
    OxygenZeroException() : runtime_error("Oxygen Failure") {}
};

class VehicleStopException : public runtime_error
{
public:
    VehicleStopException() : runtime_error("Vehicle Stop") {}
};

class Vehicle
{
public:
    Vehicle(int speed, int temperature, int energy, int humidity, int oxygenRate, int airDensity, int altitude, int length, int distance);
    Vehicle(const Vehicle &, int length);
    int getSpeed();
    int getEnergy();
    int getAltitude();
    int getOxygenRate();
    int getFlowDensity();
    int getTemperature();
    int getHumidity();
    int getDistance();
    int getLength();
    static int getUnits();
    static bool getPanelStatus();

    void setSpeed(int);
    void setEnergy(int);
    void setTemperature(int);
    void setHumidity(int);
    void setAltitude(int);
    void setOxygenRate(int);
    void setFlowDensity(int);
    void addDistance(int);
    static void setUnits(int);
    static void setPanelStatus(bool);
    virtual string name() = 0;
    virtual void move(string) = 0;
    virtual void print(int) = 0;
    void finalPrint();
    void initialPrint();
    

private:
    int speed;
    int energy;
    int temperature;
    int humidity;
    int oxygenRate;
    int flowDensity;
    int altitude;
    int distance = 0;
    static bool brokenPanel;
    static int units;
    const int length;
};
int Vehicle::units=0;
bool Vehicle::brokenPanel=false;
Vehicle::Vehicle(int speed1, int temperature1, int energy1, int humidity1, int oxygenRate1, int flowDensity1, int altitude1, int length1, int distance1 = 0)
    : length(length1)
{
    setSpeed(speed1);
    setEnergy(energy1);
    setTemperature(temperature1);
    setHumidity(humidity1);
    setOxygenRate(oxygenRate1);
    setFlowDensity(flowDensity1);
    setAltitude(altitude1);
    addDistance(distance1);
}

Vehicle::Vehicle(const Vehicle &v, int newLength) : length(v.length + newLength)
{
    speed = (v.speed);
    temperature = (v.temperature);
    energy = (v.energy);
    humidity = (v.humidity);
    oxygenRate = (v.oxygenRate);
    flowDensity = (v.flowDensity);
    altitude = (v.altitude);
    distance = v.distance;
}
int Vehicle::getSpeed()
{
    return speed;
}
int Vehicle::getEnergy()
{
    return energy;
}
int Vehicle::getTemperature()
{
    return temperature;
}
int Vehicle::getHumidity()
{
    return humidity;
}
int Vehicle::getAltitude()
{
    return altitude;
}
int Vehicle::getOxygenRate()
{
    return oxygenRate;
}
int Vehicle::getFlowDensity()
{
    return flowDensity;
}
int Vehicle::getDistance()
{
    return distance;
}
int Vehicle::getLength()
{
    return length;
}
int Vehicle::getUnits()
{
    return units;
}
bool Vehicle::getPanelStatus()
{
    return brokenPanel;
}

void Vehicle::setSpeed(int newSpeed)
{
    speed = newSpeed;
}
void Vehicle::setEnergy(int newEnergy)
{
    energy = newEnergy;
}
void Vehicle::setTemperature(int newTemperature)
{
    temperature = newTemperature;
}
void Vehicle::setHumidity(int newHumidity)
{
    humidity = newHumidity;
}
void Vehicle::setOxygenRate(int newOxygenRate)
{
    oxygenRate = newOxygenRate;
}
void Vehicle::setFlowDensity(int newFlowDensity)
{
    flowDensity = newFlowDensity;
}
void Vehicle::setAltitude(int newAltitude)
{
    altitude = newAltitude;
}
void Vehicle::setUnits(int unit)
{
    units = unit;
}
void Vehicle::addDistance(int newDistance)
{
    distance += newDistance;
}
void Vehicle::setPanelStatus(bool panelStatus)
{
    brokenPanel=panelStatus;
}
void Vehicle::finalPrint()
{
    cout << "Final Status:" << endl;
    cout << "Distance: " << getDistance() << endl;
    cout << "Energy: " << getEnergy() << endl;
    cout << "Oxygen Level: " << getOxygenRate() << endl;
    cout << endl;
}
void Vehicle::initialPrint()
{
    cout << "Current Status: Car" << endl;
    cout << "Distance: " << getDistance() << "km" << endl;
    cout << "Speed: " << 0 << "km/hr" << endl;
    cout << "Energy: " << getEnergy() << endl;
    cout << "Temperature: " << getTemperature() << " C" << endl;
    cout << "Humidity: " << getHumidity() << endl;
}
class Car : public Vehicle
{
public:
    Car(const Vehicle &, int temperature, int humidity, int length, int energy);
    Car(int newTemperature, int newLength, int newHumidity, int newEnergy);
    virtual void move(string mode) throw (EnergyZeroException, OxygenZeroException, VehicleStopException);
    virtual void print(int);
    virtual string name() {return "Car";}
    void solarPanelRecharge();
};
Car::Car(const Vehicle &v, int newTemperature, int newHumidity, int newLength, int newEnergy=1000) : Vehicle(v, newLength)
{
    setAltitude(0);
    setFlowDensity(100);
    setOxygenRate(100);
    setSpeed(80);
    setTemperature(newTemperature);
    setHumidity(newHumidity);
    if(newHumidity < 50)
        solarPanelRecharge();
}
Car::Car(int newTemperature, int newLength, int newHumidity, int newEnergy = 1000)      //for initializing
    : Vehicle(80, newTemperature, newEnergy, newHumidity, 100, 100, 0, newLength, 0)
{
    if(newHumidity < 50)
        solarPanelRecharge();
}
void Car::solarPanelRecharge()
{   
    if(!getPanelStatus())
    {
    setEnergy(getEnergy() + 200);
    if (getEnergy() > 1000)
        setEnergy(1000);
    }
}
void Car::move(string mode) throw (EnergyZeroException, OxygenZeroException, VehicleStopException)
{
    bool mode2=(mode.compare("2") == 0) ? true : false;
    int tempDistance = 0;
    do
    {
        int temperature = getTemperature();
        if (temperature > 0 && temperature < 40)
            setEnergy(getEnergy() - 5);
        else if (temperature >= 40)
            setEnergy(getEnergy() - 10);
        else if (temperature == 0)
            setEnergy(getEnergy() - 8);

        if (getHumidity() < 50)
            setEnergy(getEnergy() - 5);
        else
            setEnergy(getEnergy() - 8);

        tempDistance += 50;
        setUnits(getUnits() + 1);
        if (getEnergy() <= 0)
        {
            setEnergy(0);
            break;
        }
    } while (mode2 && getDistance() + tempDistance < getLength());

    addDistance(tempDistance);
    if (getEnergy() == 0)
        throw EnergyZeroException();
    print(tempDistance);
}

void Car::print(int tempDistance)
{
    cout << "Successfully moved to next " << tempDistance << " km" << endl;
    cout << "Current Status: Car" << endl;
    cout << "Distance: " << getDistance() << "km" << endl;
    cout << "Speed: " << getSpeed() << "km/hr" << endl;
    cout << "Energy: " << getEnergy() << endl;
    cout << "Temperature: " << getTemperature() << " C" << endl;
    cout << "Humidity: " << getHumidity() << endl;
}

class Airplane : public Vehicle
{
public:
    Airplane(const Vehicle &, int temperature, int humidity, int altitude, int airDensity, int length);
    virtual void move(string mode) throw(EnergyZeroException, OxygenZeroException, VehicleStopException);
    virtual void print(int tempDistance);
    virtual string name() {return "Airplane";}

private:
};

Airplane::Airplane(const Vehicle &v, int temperature, int humidity, int altitude, int airDensity, int length) 
: Vehicle(v, length)
{
    setTemperature(temperature);
    setHumidity(humidity);
    setAltitude(altitude);
    setFlowDensity(airDensity);
    setSpeed(900);
}

void Airplane::move(string mode) throw (EnergyZeroException, OxygenZeroException, VehicleStopException)
{
    bool mode2 = mode.compare("2") == 0 ? true : false;
    int tempDistance=0;
    bool stop = false;
    do
    {
        int air_density = getFlowDensity();
        if (air_density >= 70)
            setSpeed(400);
        else if (air_density >= 50)
            setSpeed(600);
        else if (air_density >= 30)
            setSpeed(700);
        setOxygenRate(getOxygenRate() - getAltitude() / 1000 * 10);

        int temperature = getTemperature();
        if (temperature > 0 && temperature < 40)
            setEnergy(getEnergy() - 5);
        else if (temperature >= 40)
            setEnergy(getEnergy() - 10);
        else if (temperature == 0)
            setEnergy(getEnergy() - 8);

        if (getHumidity() < 50)
        {
            setEnergy(getEnergy() - 5);
        }
        else
            setEnergy(getEnergy() - 8);

        if (getEnergy() <= 0)
        {
            setEnergy(0);
            stop = true;
        }
        if (getOxygenRate() <= 0)
        {
            setOxygenRate(0);
            stop = true;
        }
        tempDistance += 1000;
        setUnits(getUnits() + 1);
        if (getDistance()+tempDistance >= getLength())
            stop = true;
    } while (mode2 && !stop);
    addDistance(tempDistance);
    if (getEnergy() == 0)
        throw EnergyZeroException();
    else if (getOxygenRate() == 0)
        throw OxygenZeroException();
    print(tempDistance);
}
void Airplane::print(int tempDistance)
{
    cout << "Successfully moved to next " << tempDistance << " km" << endl;
    cout << "Current Status: Airplane" << endl;
    cout << "Distance: " << getDistance() << "km" << endl;
    cout << "Speed: " << getSpeed() << "km/hr" << endl;
    cout << "Energy: " << getEnergy() << endl;
    cout << "Oxygen Level: " << getOxygenRate() << endl;
    cout << "Temperature: " << getTemperature() << " C" << endl;
    cout << "Humidity: " << getHumidity() << endl;
    cout << "Altitude: " << getAltitude() << endl;
    cout << "Air Density: " << getFlowDensity() << endl;
}
class Submarine : public Vehicle
{
public:
    Submarine(const Vehicle&, int length, int temperature, int depth, int waterFlowRate);
    virtual void move(string mode) throw (EnergyZeroException, OxygenZeroException, VehicleStopException);
    virtual void print(int);
    virtual string name() {return "Submarine";}
    void light();

private:
};
Submarine::Submarine(const Vehicle& v, int newLength, int newTemperature, int newDepth, int newWaterFlowRate)
    : Vehicle(v, newLength)
{
    setTemperature(newTemperature);
    setFlowDensity(newWaterFlowRate);
    setAltitude(newDepth);
    setHumidity(100);
    setSpeed(20);
}
void Submarine::light()
{
    setEnergy(getEnergy() - 30);
}
void Submarine::move(string mode) throw(EnergyZeroException, OxygenZeroException, VehicleStopException)
{
    bool mode2=mode.compare("2") == 0 ? true : false;
    int tempDistance = 0;
    bool stop = false;
    do
    {
        int waterFlowRate = getFlowDensity();
        if (waterFlowRate >= 70)
            setSpeed(10);
        else if (waterFlowRate >= 50)
            setSpeed(15);
        else if (waterFlowRate >= 30)
            setSpeed(17);

        setOxygenRate(getOxygenRate() - getAltitude() / 50 * 5);

        int temperature = getTemperature();
        if (temperature > 0 && temperature < 40)
            setEnergy(getEnergy() - 5);
        else if (temperature >= 40)
            setEnergy(getEnergy() - 10);
        else if (temperature == 0)
            setEnergy(getEnergy() - 8);

        light();
        if (getEnergy() <= 0)
        {
            setEnergy(0);
            stop = true;
        }
        if (getOxygenRate() <= 0)
        {
            setOxygenRate(0);
            stop = true;
        }
        tempDistance += 10;
        setUnits(getUnits() + 1);
        if (getDistance() + tempDistance >= getLength())
            stop = true;
    } while (mode2 && !stop); 
    addDistance(tempDistance);
    if (getEnergy() == 0)
        throw EnergyZeroException();
    else if (getOxygenRate() == 0)
        throw OxygenZeroException();
    print(tempDistance);
}
void Submarine::print(int tempDistance)
{
    cout << "Successfully moved to next " << tempDistance << " km" << endl;
    cout << "Current Status: Submarine" << endl;
    cout << "Distance: " << getDistance() << "km" << endl;
    cout << "Speed: " << getSpeed() << "km/hr" << endl;
    cout << "Energy: " << getEnergy() << endl;
    cout << "Oxygen Level: " << getOxygenRate() << endl;
    cout << "Temperature: " << getTemperature() << " C" << endl;
    cout << "Depth: " << getAltitude() << endl;
    cout << "Water Flow: " << getFlowDensity() << endl;
}

class BlackBox
{
public:
    void print();
    void recordMode(string);
    void recordEnergy(int);
    void recordOxygen(int);
    void recordSpeed(int);
    void record(Vehicle& vehicle)
    {
    recordMode(vehicle.name());
    recordEnergy(vehicle.getEnergy());
    recordSpeed(vehicle.getSpeed());
    recordOxygen(vehicle.getOxygenRate());
    }
private:
    string mode = "Mode: ";
    string energyLevel = "Energy Level: ";
    string oxygenLevel = "Oxygen Level: ";
    string speed = "Speed: ";
    string recentMode = "";
    string recentEnergy = "";
    string recentOxygen = "";
    string recentSpeed = "";
};

void BlackBox::print()
{
    cout << "Blackbox:" << endl;
    cout << mode << endl;
    cout << energyLevel << endl;
    cout << oxygenLevel << endl;
    cout << speed << endl;
    cout << "--------------------" << endl;
}
void BlackBox::recordEnergy(int energy)
{
    string stringEnergy = to_string(energy);
    if (stringEnergy.compare(recentEnergy) != 0)
    {
        if(energyLevel.compare("Energy Level: ") == 0)
            energyLevel += stringEnergy + " ";
        else
            energyLevel += "> " + stringEnergy + " ";
        recentEnergy=stringEnergy;
    }
}
void BlackBox::recordMode(string newMode)

{
    if (newMode.compare(recentMode) != 0)
    {
        if(mode.compare("Mode: ") == 0)
            mode += newMode + " ";
        else 
            mode += "> " + newMode + " ";
        recentMode = newMode;
    }        
}
void BlackBox::recordOxygen(int oxygenRate)
{
    string stringOxygen = to_string(oxygenRate);
    if (stringOxygen.compare(recentOxygen) != 0)
    {
        if(oxygenLevel.compare("Oxygen Level: ") == 0)
            oxygenLevel += stringOxygen + " ";
        else
            oxygenLevel += "> " + stringOxygen + " ";
        recentOxygen = stringOxygen;
    }
}
void BlackBox::recordSpeed(int newSpeed)
{
    string stringSpeed = to_string(newSpeed);
    if (stringSpeed.compare(recentSpeed) != 0)
    {
        if(speed.compare("Speed: ") == 0)
            speed += stringSpeed;
        else
            speed += "> " + stringSpeed + " ";
        recentSpeed = stringSpeed;
    }
}

vector<char *> textVector(int);
Vehicle *initialVehicle(vector<char *>, BlackBox&);
Vehicle *vehicleType(vector<char *> , int, BlackBox&, Vehicle*);
int checkXY(vector<char*> , int, Vehicle*) throw (VehicleStopException);
string graphic(vector<char *> , int);
int getRandomNumber(int);
int main()
{
    cout << "PJ1.P C H.2014-17082" << endl;
    cout << "Mode Select(1 for EXTRA, 2 for NORMAL) :";
    int includeXY;
    cin >> includeXY;
        
    std::srand(static_cast<unsigned int>(std::time(0)));    
    while (true)
    {
        Vehicle::setPanelStatus(false);
        BlackBox blackbox;
        Vehicle::setUnits(0);
        cout << "Choose the number of the test case (1~10) : ";
        int testNum;
        cin >> testNum;
        if(testNum == 0) 
            return 0;
        cout << "Test case #" << testNum << "." << endl;

        Vehicle* myVehicle = NULL;
        myVehicle = initialVehicle(textVector(testNum), blackbox);
        myVehicle -> initialPrint();
        cout << graphic(textVector(testNum), 0) << endl;
        cout << "Next Move? (1,2)" << endl;
        cout << "CP-2014-17082>";
        string mode;
        getline(cin, mode);
        while (mode.compare("1") != 0 && mode.compare("2") != 0)
        {
            getline(cin, mode);
        }
        try
        {
            int i = 0;
            for (; i < textVector(testNum).size(); i++)
            {
                string currentJourney;
                myVehicle = vehicleType(textVector(testNum), i, blackbox, myVehicle);
                while (myVehicle -> getDistance() < myVehicle -> getLength())
                {
                    myVehicle -> move(mode);
                    currentJourney = graphic(textVector(testNum), Vehicle::getUnits());
                    if(currentJourney.at(currentJourney.length() - 2) == '@')
                        break;
                    cout << currentJourney << endl;
                    cout << "Next Move? (1,2)" << endl;
                    cout << "CP-2014-17082>";
                    getline(cin, mode);
                    while (mode.compare("1") != 0 && mode.compare("2") != 0)
                    {
                        cout << "CP-2014-17082>";
                        getline(cin, mode);
                    }
                }
                blackbox.record(*myVehicle);
                if(includeXY == 1)
                    {
                        i += checkXY(textVector(testNum), i + 1, myVehicle);
                    }
            }
            myVehicle -> finalPrint();
            cout << graphic(textVector(testNum), Vehicle::getUnits()) << endl;
            cout << "!Finished : Arrived" << endl;
        }
        catch (const EnergyZeroException &e)
        {
            myVehicle->finalPrint();
            string entireJourney = graphic(textVector(testNum), Vehicle::getUnits());
            cout << entireJourney << endl;
            if(entireJourney.at(entireJourney.length() - 2) == '@')
                cout << "!Finished : Arrived" << endl;
            else
                cout << "!Finished : " << e.what() << endl;
        }
        catch (const OxygenZeroException &e)
        {
            myVehicle->finalPrint();
            string entireJourney = graphic(textVector(testNum), Vehicle::getUnits());
            cout << entireJourney << endl;
            if(entireJourney.at(entireJourney.length() - 2) == '@')
                cout << "!Finished : Arrived" << endl;
            else
                cout << "!Finished : " << e.what() << endl;
        }
        catch (const VehicleStopException &e)
        {
            myVehicle->finalPrint();
            string entireJourney = graphic(textVector(testNum), Vehicle::getUnits());
            cout << entireJourney << endl;
            if(entireJourney.at(entireJourney.length() - 2) == '@')
                cout << "!Finished : Arrived" << endl;
            else
                cout << "!Finished : " << e.what() << endl;
        }
        blackbox.record(*myVehicle);
        blackbox.print();
        delete myVehicle;
    }
    return 0;
}

vector<char *> textVector(int num)
{
    char *pch;
    const char *delimiter = ",";
    vector<char *> a;

    string TC[10];
    TC[0] = "[R200T25H10],[S2000T20H0A1000D20],[O30T10D500W0]";
    TC[1] = "[R200T0H0],[X],[Y],[S2000T0H60A1000D70],[X],[O30T10D200W10]";
    TC[2] = "[R50T20H30],[S3000T40H5A2000D20],[X],[O80T0D100W100],[R150T30H50]";
    TC[3] = "[R4000T10H10],[O10T0D100W10],[Y],[R200T60H100]";
    TC[4] = "[R500T20H20],[S3000T10H5A2000D50],[O80T0D100W100]";
    TC[5] = "[R5000T10H10]";
    TC[6] = "[R50T10H10],[Y],[S4000T10H5A2000D72],[R50T10H10],[O100T0D100W100],[R50T10H60]";
    TC[7] = "[R2500T45H50],[S4000T10H5A2000D100],[O20T0D100W100]";
    TC[8] = "[R2500T45H50],[S4000T10H5A2000D100],[O40T0D100W100]";
    TC[9] = "[R3400T10H10],[S3000T10H5A2000D52],[Y],[O10T0D100W10]";
    string str = TC[num - 1];
    char cstr[2000];
    strcpy(cstr, str.c_str());
    pch = strtok(cstr, delimiter);
    while (pch != NULL)
    {
        a.push_back(pch);
        pch = strtok(NULL, delimiter);
    }
    return a;
}

Vehicle *initialVehicle(vector<char *> a, BlackBox& blackbox)
{
    Vehicle *newVehicle = NULL;
    char *strsub = new char[2000];
    strcpy(strsub, a.at(0));
    const char *delimiterSub = "[]RTH";
    
    char *pchsub;
    char* b[5];
    pchsub = strtok(strsub, delimiterSub);
    int j = 0;
    while (pchsub != NULL)
    {
        b[j] = pchsub;
        j++;
        pchsub = strtok(NULL, delimiterSub);
    }
    newVehicle = new Car(atoi(b[1]), 0, atoi(b[2]));
    delete[] strsub;
    return newVehicle;
}
Vehicle *vehicleType(vector<char *> a, int i, BlackBox& blackbox,Vehicle *v)
{
    Vehicle *newVehicle=NULL;
    char *strsub = new char[2000];
    strcpy(strsub, a.at(i));
    const char *delimiterSub = NULL;
    char roadCondition = strsub[1];
    if (roadCondition == 'R')
       delimiterSub = "[]RTH";
    else if (roadCondition == 'S')
        delimiterSub = "[]STHAD";
    else if (roadCondition == 'O')
        delimiterSub = "[]OTDW";
    else
        return v;
    char *pchsub;
    char* b[5];
    pchsub = strtok(strsub, delimiterSub);
    int j = 0;
    while (pchsub != NULL)
    {
        b[j] = (pchsub);
        j++;
        pchsub = strtok(NULL, delimiterSub);
    }
    int length;
    int temperature;
    int humidity;
    int altitude;
    int flowDensity;
    switch (roadCondition)
    {
    case 'R':
        length = atoi(b[0]);
        temperature = atoi(b[1]);
        humidity = atoi(b[2]);
        newVehicle = new Car(*v, temperature, humidity, length);
        blackbox.recordMode("Car");
        break;
    case 'S':
        length = atoi(b[0]);
        temperature = atoi(b[1]);
        humidity = atoi(b[2]);
        altitude = atoi(b[3]);
        flowDensity = atoi(b[4]);
        newVehicle = new Airplane(*v, temperature, humidity, altitude, flowDensity, length);
        blackbox.recordMode("Airplane");
        break;
    case 'O':
        length = atoi(b[0]);
        temperature = atoi(b[1]);
        altitude = atoi(b[2]);
        flowDensity = atoi(b[3]);
        newVehicle = new Submarine(*v, length, temperature, altitude, flowDensity);
        blackbox.recordMode("Submarine");
        break;
    default:
        newVehicle = v;
    }
    delete v;
    delete[] strsub;
    return newVehicle;
}

string graphic(vector<char *> a, int units)
{
	string roadGraphic = "";
    int j = 0;
	for (int i = 0; i < a.size(); i++)
	{
		char* tempTc = new char[2000];
		strcpy(tempTc, a.at(i));
		const char *delimiterSub = NULL;
		int unit;
		char roadSign;
		if (tempTc[1] == 'R')
		{
			delimiterSub = "RT";
			unit = 50;
			roadSign = '=';
		}
		else if (*(tempTc + 1) == 'S')
		{
			delimiterSub = "ST";
			unit = 1000;
			roadSign = '^';
		}
		else if (*(tempTc + 1) == 'O')
		{
			delimiterSub = "OT";
			unit = 10;
			roadSign = '~';
		}
        else
            continue;
		char *pchsub = strtok(tempTc, delimiterSub);
		pchsub = strtok(NULL, delimiterSub);
		int roadNum = atoi(pchsub);
        int tempj = j;
		for (; j - tempj < roadNum / unit; j++)
		{
			if (j == units)
				roadGraphic += '@';
			roadGraphic += roadSign;
		}
        delete[] tempTc;
	}
    if (j == units)
        roadGraphic += '@';
	return "|" + roadGraphic + "|";
}
int getRandomNumber(int max)
{
    return static_cast<int>(max*rand()/(RAND_MAX+1.0));
}
int checkXY(vector<char*> a, int i, Vehicle* myVehicle) throw (VehicleStopException)
{
    int situations = 0;
    while(a.size() > i + situations)
    {
        char *strsub = a.at(i + situations);
        if (strsub[1] == 'X')
        {
            int x = getRandomNumber(10);
            if (x <= 2)
                throw VehicleStopException();
            else
                myVehicle->setEnergy(myVehicle -> getEnergy() - 100);
            situations++;
            continue;
        }

        else if (*(strsub + 1) == 'Y')
        {
            int y = getRandomNumber(1000);
            if (y <= 350)
                throw VehicleStopException();
            else if (y > 675)
            {
                if (myVehicle -> name().compare("Car") == 0)
                    Vehicle::setPanelStatus(true);
                else
                    myVehicle -> setOxygenRate(myVehicle->getOxygenRate() - 30);
            }
            situations++;
            continue;
        }
        break;
    }
    return situations;
}