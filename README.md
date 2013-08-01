#"Capemgr" for BeagleBone Black

C api for BeagleBone Black, functions for gpio, analog, pwm, i2c and bbb tool and more...

### bbb:

      BeagleBone Black                                                
      ----------------                                                
                                                                      
      --show-all                                                      
      --show-pin <P[HEADER]_[NUM]>                                    
      --show-by-type <type>                                           
      --show-by-type-only <type>                                      
      --show-types                                                    
                                                                      
      --enable-adc                                                    
      --get-adc <id>                                                  
                                                                      
      --i2c-scan <bus>                                                
      --enable-i2c-device <bus>                                       
         --address <address>                                          
         --module <module>                                            
                                                                      
      --disable-i2c-device <bus>                                      
         --address <address>                                          
                                                                      
      --enable-gpio <gpio>                                            
      --enable-gpio-pin <P[HEADER]_[NUM]>                             
      --disable-gpio <gpio>                                           
      --disable-gpio-pin <P[HEADER]_[NUM]>                            
                                                                      
      --gpio <gpio>                                                   
      --gpio-pin <P[HEADER]_[NUM]>                                    
         --set-direction <0 | 1>                                      
         --get-direction                                              
         --set-value <0 | 1>                                          
         --get-value                                                  
                                                                      
      --enable-pwm <P[HEADER]_[NUM]>                                  
      --pwm <P[HEADER]_[NUM]>                                         
         --set-period <x[Hz][kHz][MHz]>                               
         --set-duty <[0-100]>                                         
         --get-period                                                 
         --get-duty                                                   
                                                                      
    Examples:                                                         
                                                                      
    sudo ./bbb --enable-adc                                           
    sudo ./bbb --get-adc 2                                            
                                                                      
    sudo ./bbb --enable-i2c-device 1 --address 0x53 --module adxl34x  
    sudo ./bbb --i2c-scan 1                                           
    sudo ./bbb --disable-i2c-device 1 --address 0x53                  
                                                                      
         ./bbb --show-all                                             
         ./bbb --show-pin P8_13                                       
         ./bbb --show-by-type-only pwm                                
                                                                      
    sudo ./bbb --enable-gpio 60                                       
    sudo ./bbb --gpio 60 --set-direction 1                            
    sudo ./bbb --gpio 60 --get-direction                              
    sudo ./bbb --gpio 60 --set-value 1                                
    sudo ./bbb --gpio 60 --get-value                                  
    sudo ./bbb --disable-gpio 60                                      
                                                                      
    sudo ./bbb --enable-pwm P8_13                                     
    sudo ./bbb --pwm --set-period 50Hz --set-duty 50                  
    sudo ./bbb --pwm --get-period --get-duty

### Build:
    
    git clone https://github.com/vmolsa/lib-bbb.git
    cd lib-bbb
    make
