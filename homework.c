#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10

typedef struct
{
    char name[20];
    double x, y;

} MetroStation;

typedef struct
{
    char color[20];
    MetroStation MetroStations[SIZE];
    int count;

} MetroLine;

typedef struct
{
    MetroLine MetroLines[SIZE];
    int count;

} MetroSystem;

int equals(MetroStation s1, MetroStation s2)
{
    return (strcmp(s1.name, s2.name) == 0 ? 1 : 0);
}

void addStation(MetroLine *line, MetroStation station)
{
    if (line->count < SIZE)
    {
        line->MetroStations[line->count] = station;
        line->count++;
    }
}

int hasStation(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            return 1;
        }
    }
    return 0;
}

MetroStation getFirstStop(MetroLine line)
{
    if (line.count > 0)
    {
        return line.MetroStations[0];
    }
    else
    {
        MetroStation station;
        strcpy(station.name, "NULL");
        station.x = 0;
        station.y = 0;
        return station;
    }
}

MetroStation getPreviousStop(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            if (i > 0)
            {
                return line.MetroStations[i - 1];
            }
            else
            {
                MetroStation st;
                strcpy(st.name, "NULL");
                st.x = 0;
                st.y = 0;
                return st;
            }
        }
    }
    MetroStation st;
    strcpy(st.name, "NULL");
    st.x = 0;
    st.y = 0;
    return st;
}

MetroStation getNextStop(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            if (i == line.count - 1)
            {
                MetroStation st;
                strcpy(st.name, "NULL");
                st.x = 0;
                st.y = 0;
                return st;
            }
            else
            {
                return line.MetroStations[i + 1];
            }
        }
    }
    MetroStation st;
    strcpy(st.name, "NULL");
    st.x = 0;
    st.y = 0;
    return st;
}

void addLine(MetroSystem *system, MetroLine line)
{
    if (system->count < SIZE)
    {
        system->MetroLines[system->count] = line;
        system->count++;
    }
}

void printLine(MetroLine line)
{
    for (int i = 0; i < line.count; i++)
    {
        printf("%s\n", line.MetroStations[i].name);
    }
}

void printPath(MetroLine line)
{
    for (int i = 0; i < line.count; i++)
    {
        printf("%s\n", line.MetroStations[i].name);
    }
}

double getDistanceTravelled(MetroStation stations[])
{
    double distance = 0;
    int count = sizeof(stations) / sizeof(stations[0]);
    if (count > 1)
    {
        for (int i = 0; i < count - 1; i++)
        {
            distance += sqrt(pow(stations[i + 1].x - stations[i].x, 2) + pow(stations[i + 1].y - stations[i].y, 2));
        }
    }
    return distance;
}

// may need to change this
MetroStation findNearestStation(MetroSystem system, double x, double y)
{
    MetroStation nearestStation;
    strcpy(nearestStation.name, "NULL");
    nearestStation.x = 0;
    nearestStation.y = 0;
    double distance = 0;
    for (int i = 0; i < system.count; i++)
    {
        for (int j = 0; j < system.MetroLines[i].count - 1; j++)
        {
            if (j == 0)
            {
                MetroStation firstStop = getFirstStop(system.MetroLines[i]);
                distance = sqrt(pow(firstStop.x - x, 2) + pow(firstStop.y - y, 2));
                nearestStation = firstStop;
            }
            else
            {
                MetroStation nextStop = getNextStop(system.MetroLines[j], nearestStation);
                double newDistance = sqrt(pow(nextStop.x - x, 2) + pow(nextStop.y - y, 2));
                if (newDistance < distance)
                {
                    distance = newDistance;
                    nearestStation = system.MetroLines[i].MetroStations[j];
                }
            }
        }
    }
    return nearestStation;
}

void getNeighboringStations(MetroSystem system, MetroStation station, MetroStation neighboringStations[])
{
    int count = 0;
    for (int i = 0; i < system.count; i++)
    {
        for (int j = 0; j < system.MetroLines[i].count; j++)
        {
            if (hasStation(system.MetroLines[i], station))
            {
                if (j == 0)
                {
                    MetroStation firstStop = getFirstStop(system.MetroLines[i]);
                    if (!equals(firstStop, station))
                    {
                        neighboringStations[count] = firstStop;
                        count++;
                    }
                }
                else
                {
                    MetroStation previousStop = getPreviousStop(system.MetroLines[i], station);
                    if (!equals(previousStop, station))
                    {
                        neighboringStations[count] = previousStop;
                        count++;
                    }
                }
                if (j == system.MetroLines[i].count - 1)
                {
                    MetroStation lastStop = getFirstStop(system.MetroLines[i]);
                    if (!equals(lastStop, station))
                    {
                        neighboringStations[count] = lastStop;
                        count++;
                    }
                }
                else
                {
                    MetroStation nextStop = getNextStop(system.MetroLines[i], station);
                    if (!equals(nextStop, station))
                    {
                        neighboringStations[count] = nextStop;
                        count++;
                    }
                }
            }
        }
    }
}


    
int main(int argc, char const *argv[])
{
    MetroSystem system;
    system.count = 0;
    MetroLine line;
    MetroStation station;
    strcpy(station.name, "NULL");
    station.x = 0;
    station.y = 0;
    strcpy(line.color, "NULL");
    line.count = 0;
    addLine(&system, line);
    MetroLine line1;
    MetroStation station1;
    strcpy(station1.name, "NULL");
    station1.x = 0;
    station1.y = 0;
    strcpy(line1.color, "NULL");
    line1.count = 0;
    addLine(&system, line1);

    return 0;
}
