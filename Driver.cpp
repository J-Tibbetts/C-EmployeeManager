#include"employeeManager.h"
using namespace std;


const float Paycheck::FED_TAX_RATE = 0.15;
const float Paycheck::STATE_TAX_RATE = 0.0625;
const float Paycheck::FICA_RATE = 0.0625;

int main() {
	EmployeeManager employeeManager;
	employeeManager.start();
	return 0;
}