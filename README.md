# WebServerRemoteControl
# RELEASE_VERSION - v2024.3

## API example
   ####  http://192.168.1.106/26/on
   ####  http://192.168.1.106/26/off

   ####  http://192.168.1.106/27/on
   ####  http://192.168.1.106/27/off

## Comands Serial Monitor

### 1 Chanel
  ### Запит
    #### request_ch_1_power_on - вкл кнопку power на датчику
    #### request_ch_1_power_off - викл кнопку power на датчику
    #### request_ch_1_tamper_on - вкл кнопку tamper на датчику
    #### request_ch_1_tamper_off - викл кнопку tamper на датчику
  ### Відповідь на запит, якщо запит був успішний
    #### response_ch_1_power_on - вкл кнопку power на датчику
    #### response_ch_1_power_off - викл кнопку power на датчику
    #### response_ch_1_tamper_on - вкл кнопку tamper на датчику
    #### response_ch_1_tamper_off - викл кнопку tamper на датчику

### 2 Chanel
  ### Запит
    #### request_ch_2_power_on - вкл кнопку power на датчику
    #### request_ch_2_power_off - викл кнопку power на датчику
    #### request_ch_2_tamper_on - вкл кнопку tamper на датчику
    #### request_ch_2_tamper_off - викл кнопку tamper на датчику
  ### Відповідь на запит, якщо запит був успішний
    #### response_ch_2_power_on - вкл кнопку power на датчику
    #### response_ch_2_power_off - викл кнопку power на датчику
    #### response_ch_2_tamper_on - вкл кнопку tamper на датчику
    #### response_ch_2_tamper_off - викл кнопку tamper на датчику

### 3 Chanel
  ### Запит
    #### request_ch_3_power_on - вкл кнопку power на датчику
    #### request_ch_3_power_off - викл кнопку power на датчику
    #### request_ch_3_tamper_on - вкл кнопку tamper на датчику
    #### request_ch_3_tamper_off - викл кнопку tamper на датчику
  ### Відповідь на запит, якщо запит був успішний
    #### response_ch_3_power_on - вкл кнопку power на датчику
    #### response_ch_3_power_off - викл кнопку power на датчику
    #### response_ch_3_tamper_on - вкл кнопку tamper на датчику
    #### response_ch_3_tamper_off - викл кнопку tamper на датчику

### Системні запити
  #### release_version - повертає версію прошивки

## User interface
![UI Interface Screenshot](./Screenshot-ui-interface.png)
