#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

bool ackReceived = true;
int currentFrame = 0;
int totalFrames = 10;
const int TIMEOUT = 3000; // Timeout in milliseconds

void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds) {
        // Do nothing, just wait
    }
}

bool simulateFrameLoss() {
    return rand() % 2 == 0; // 50% chance of frame loss
}

void sender(int& frameToSend) {
    if (ackReceived && frameToSend < totalFrames) {
        ackReceived = false;
        cout << "Sender: Sent frame " << frameToSend+1 << endl;
        // Simulate sending time
        delay(500);
    }
}

void receiver(int frameToReceive) {
    if (!ackReceived) {
        // Simulate frame loss
        if (!simulateFrameLoss()) {
            cout << "Receiver: Frame " << frameToReceive+1 << " lost" << endl;
            // Simulate resend time
            delay(TIMEOUT);
        } else {
            cout << "Receiver: Received frame " << frameToReceive+1 << endl;
            ackReceived = true;
        }
    }
}

void simulateStopAndWaitProtocol() {
    while (currentFrame < totalFrames) {
        sender(currentFrame);
        receiver(currentFrame);
        if (ackReceived) {
            currentFrame++;
        }
    }
}

int main() {
    srand(time(0)); // Seed for random number generation
    cout << "Stop and Wait Protocol Simulation" << endl;
    simulateStopAndWaitProtocol();
    return 0;
}
