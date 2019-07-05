BLA::Matrix<3> *accelCorrection(int n, BLA::Matrix<3> accel, BLA::Matrix<3> accelPreviousAvrg) {
	Serial.print("STAY STATIC!!!");
	Serial.print("Correction would start in 1s");
	delay(1000);
	BLA::Matrix<3> result = (accelPreviousAvrg * (n-1) + accel)/n;
	BLA::Matrix<3> *pointer = &result;
	return pointer;
}
