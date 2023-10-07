

```
external_components:
  - source: github://slimcdk/esphome-custom-components@master
    components: [ tmc2300 ]


logger: ...
wifi: ...
api: ...


esp32:
  board: ...
  variant: ...
  framework:
    type: esp-idf
    sdkconfig_options:
      CONFIG_COMPILER_OPTIMIZATION_SIZE: y
    advanced:
      ignore_efuse_mac_crc: true


uart:
  tx_pin: 4
  rx_pin: 5
  baud_rate: 500000


esphome:
  name: tmc2300-driver
  on_boot:
    - lambda: |
        id(tmc2300_stepper).set_microsteps(256);
        id(tmc2300_stepper).stallguard_sgthrs(400);

stepper:
  - platform: tmc2300
    id: tmc2300_stepper
    diag_pin: 9
    on_fault_signal:
      - logger.log: "Motor stalled!"
    max_speed: 250 # required, but not used

```