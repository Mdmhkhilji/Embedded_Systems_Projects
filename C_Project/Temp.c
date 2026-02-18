#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define THRESHOLD 95.0

int main() {
    FILE *inputFile, *alertFile;
    char line[MAX_LINE];
    char timestamp[50], sensor_id[20];
    float temperature;

    float sum = 0.0, max = -1000.0, min = 1000.0;
    int count = 0;

    inputFile = fopen("Temperature_Data.csv", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    alertFile = fopen("Temperature_alerts.csv", "w");
    if (alertFile == NULL) {
        printf("Error: Unable to create alert file.\n");
        fclose(inputFile);
        return 1;
    }

    /* Write header for alert file */
    fprintf(alertFile, "Timestamp,Sensor ID,Temperature\n");

    /* Skip CSV header */
    fgets(line, MAX_LINE, inputFile);

    printf("\nTemperature Trend Summary\n");
    printf("--------------------------------------------------\n");
    printf("Timestamp\t\tSensor\tTemp (Â°C)\tStatus\n");
    printf("--------------------------------------------------\n");

    while (fgets(line, MAX_LINE, inputFile)) {
        if (sscanf(line, "%49[^,],%19[^,],%f", timestamp, sensor_id, &temperature) != 3)
            continue;

        sum += temperature;
        count++;

        if (temperature > max) max = temperature;
        if (temperature < min) min = temperature;

        if (temperature > THRESHOLD) {
            fprintf(alertFile, "%s,%s,%.2f\n", timestamp, sensor_id, temperature);
            printf("%s\t%s\t%.2f\t\tALERT\n", timestamp, sensor_id, temperature);
        } else {
            printf("%s\t%s\t%.2f\t\tNORMAL\n", timestamp, sensor_id, temperature);
        }
    }

    fclose(inputFile);
    fclose(alertFile);

    if (count == 0) {
        printf("\nNo temperature data found.\n");
        return 1;
    }

    printf("--------------------------------------------------\n");
    printf("Summary Metrics\n");
    printf("--------------------------------------------------\n");
    printf("Average Temperature : %.2f Â°C\n", sum / count);
    printf("Maximum Temperature : %.2f Â°C\n", max);
    printf("Minimum Temperature : %.2f Â°C\n", min);
    printf("--------------------------------------------------\n");

    printf("\nAlert file generated: temperature_alerts.csv\n");

    return 0;
}
