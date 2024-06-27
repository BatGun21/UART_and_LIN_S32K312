# UART and LIN on S32K312

This project demonstrates the implementation of UART and LIN communication protocols on the S32K312 microcontroller using polling. The code initializes the UART interface, sends a welcome message, and echoes back any received data. It also controls LEDs based on a timer.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Setup](#setup)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project provides a basic example of UART communication on the S32K312 microcontroller. The code handles UART communication with an echo back mechanism and controls LEDs based on a timer interrupt.

### Features

- UART communication with polling
- Echo back functionality for received data
- LED control based on a timer

## Prerequisites

Before using this project, ensure you have the following:

- **S32K312 Development Board**
- **S32 Design Studio (S32DS)**
- **Debugging Interface (e.g., J-Link, OpenSDA)**

## Setup

Follow these steps to set up and run the project:

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/BatGun21/UART_and_LIN_S32K312.git
    cd UART_and_LIN_S32K312
    ```

2. **Open in S32 Design Studio**:

    - Launch S32 Design Studio.
    - Import the project into your workspace (`File -> Import -> Existing Projects into Workspace`).

3. **Build the Project**:

    - Right-click on the project in the Project Explorer.
    - Select `Build Project`.

4. **Program the Microcontroller**:

    - Connect your development board to the PC.
    - Use the debug interface to flash the binary onto the microcontroller.

## Usage

Once the project is programmed on the microcontroller:

1. **Connect UART**:

    - Use a UART-to-USB converter or a direct UART connection to interface with your PC.

2. **Open a Serial Terminal**:

    - Configure a serial terminal (e.g., PuTTY, Tera Term) to the appropriate COM port with the settings matching your UART configuration (e.g., 9600 baud, 8 data bits, no parity, 1 stop bit).

3. **Interact with UART**:

    - Upon reset, the microcontroller sends a welcome message: `"Hello, UART! Type something to echo back:"`.
    - Type any text in the terminal and observe it being echoed back by the microcontroller.
