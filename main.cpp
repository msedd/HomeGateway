// Do not remove the include below
#include "main.h"
#include "HomeGateway.h"

HomeGateway* homeGateway = 0;

void setup() {

	homeGateway = new HomeGateway();
}

void loop() {

	homeGateway->onLoop();
}
