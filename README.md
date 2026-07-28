# PIEC 2.0

System sterowania piecem do wypału elementów kompozytowych. Projekt obejmuje zarówno autorski projekt warstwy sprzętowej (PCB), jak i oprogramowanie wbudowane zarządzające procesem obróbki termicznej.

Serce układu stanowi mikrokontroler **STM32F405RGT6** z rdzeniem ARM Cortex-M4.

## Architektura Sprzętowa 

*   **Pomiary Temperatur:**
    *   4 niezależne kanały pomiarowe zoptymalizowane pod dokładne czujniki **PT1000**.
*   **Sterowanie Mocą:**
    *   Izolowane wyjścia dla zewnętrznych przekaźników SSR zarządzające grzałkami oraz wentylatorem.
    *   Sterowanie tranzystorowe z diodami sygnalizacyjnymi na panelu przednim.
*   **Interfejs Użytkownika:**
    *   Złącze dla wyświetlacza LCD SPI.
    *   4 przyciski funkcyjne na panelu przednim.
    *   Sygnalizator dźwiękowy Buzzer.
*   **Logowanie danych:**
    *   Gniazdo na kartę **SD** obsługiwane przez interfejs SDIO.

## Oprogramowanie Wbudowane 

Projekt został stworzony w środowisku STMCube i napisany w języku C. Kod zawiera sterowanie pomiarami temeratury oraz system wysterowywania grzałek.

**Projekt nie jest jeszcze ukończony.**
