/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "isrHandler.h"

// the events variable
volatile uint32_t events = 0;

// drive payload struct
static struct drivePayload {
    int leftWheels;
    int rightWheels;
    int cameraPan;
    int cameraTilt;
    int cameraNum;
} DrivePayload;

// uart0 - comm with computer state machine:
#define PREAMBLE0 0xEA
#define PREAMBLE1 0xE3
static enum driveStates_e { pre0, pre1, lwlo, lwhi, rwlo, rwhi,
    panlo, panhi, tiltlo, tilthi, cameraNum } driveState;

// drive payload:
// [LWlo, LWhi, RWlo, RWhi, Panlo, Panhi, Tiltlo, Tilthi, camera#]
// TODO: test video mux
// Assuming 3 cameras...
#define CAMERA0_PWM 1000
#define CAMERA1_PWM 1500
#define CAMERA2_PWM 2000

void uart0_eventHandler() {
    // get next element in uart rx buffer
    uint8_t data = (uint8_t) UART0_UartGetByte();
    
    // handle events variable: only clear if uart rx buff is empty
    if (UART0_SpiUartGetRxBufferSize() == 0) {
        events &= ~EVENT_UART0;
    }
    
    // drive state machine:
    switch (driveState) {
    case pre0:
        if (data == PREAMBLE0) {
            driveState = pre1;
        }
        break;
    case pre1:
        if (data == PREAMBLE1) {
            driveState = lwlo;
        }
        else {
            driveState = pre0;
        }
        break;
    case lwlo:
        // get the new left wheel data
        DrivePayload.leftWheels = data;
        driveState = lwhi;
        break;
    case lwhi:
        DrivePayload.leftWheels |= (0xff00 & (data << 8));
        // now update left wheels pwm timer:
        LeftDrive_WriteCompare(DrivePayload.leftWheels);
        driveState = rwlo;
        break;
    case rwlo:
        // get the new right wheel data
        DrivePayload.rightWheels = data;
        driveState = rwhi;
        break;
    case rwhi:
        DrivePayload.rightWheels |= (0xff00 & (data << 8));
        // now update right wheels pwm timer:
        RightDrive_WriteCompare(DrivePayload.rightWheels);
        driveState = panlo;
        break;
    case panlo:
        // get the new camera pan data
        DrivePayload.cameraPan = data;
        driveState = panhi;
        break;
    case panhi:
        DrivePayload.cameraPan |= (0xff00 & (data << 8));
        // now update camera pan pwm timer:
        CameraGimbal_WriteCompare1(DrivePayload.cameraPan);
        driveState = tiltlo;
        break;
    case tiltlo:
        // get new camera tilt data
        DrivePayload.cameraTilt = data;
        driveState = tilthi;
        break;
    case tilthi:
        DrivePayload.cameraTilt |= (0xff00 & (data << 8));
        // update camera tilt pwm timer
        CameraGimbal_WriteCompare2(DrivePayload.cameraTilt);
        driveState = cameraNum;
        break;
    case cameraNum:
        // get camera number:
        DrivePayload.cameraNum = data;
        // TODO: update camera mux...
        if (DrivePayload.cameraNum == 0) {
            
        }
        else if (DrivePayload.cameraNum == 1) {
            
        }
        else if (DrivePayload.cameraNum == 2) {
            
        }
        driveState = pre0;
        break;
    default:
        driveState = pre0;
        break;
    }
    
}

/* [] END OF FILE */
