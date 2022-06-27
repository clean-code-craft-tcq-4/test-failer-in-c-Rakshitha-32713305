#include <stdio.h>
#include <assert.h>

#define PRODUCTION_CODE_ENABLE  STD_ON 
#define NETWORK_ALERT_THRESHOLDLEVEL 200


#if (PRODUCTION_CODE_ENABLE == STD_OFF)
int alertFailureCount = 0;
int networkAlertStub(float celcius )
{   
    int ret =0;
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if (celcius < NETWORK_ALERT_THRESHOLDLEVEL)
    {
    // Return 200 for ok
        ret = 200 ;
    }
    else 
    {
    // Return 500 for not-ok
      ret = 500 ;
    }
    return ret;
}

void networkAlert_belowthreshold_test (float celcius)
{
    if (celcius < NETWORK_ALERT_THRESHOLDLEVEL)
         {
             assert(networkAlertStub(celcius)==200);
         }      
}

void networkAlert_abovethreshold_test (float celcius)
{
    if (celcius >= NETWORK_ALERT_THRESHOLDLEVEL)
         {
            assert(networkAlertStub(celcius)==500);
            assert(alertFailureCount != 0);    
         }   
}
#endif

void alertInCelcius(float farenheit)
{
    float celcius = (farenheit - 32) * 5 / 9;    
#if (PRODUCTION_CODE_ENABLE == STD_OFF)    
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200)
    {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
    networkAlert_abovethreshold_test(celcius);
    networkAlert_belowthreshold_test(celcius); 
    printf("%d alerts failed.\n", alertFailureCount);
#endif

}

int main()
{
    alertInCelcius(400.5);
    alertInCelcius(303.6);   
    printf("All is well (maybe!)\n");
    return 0;
}
