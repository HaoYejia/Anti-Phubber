BLA::Matrix<3> *headingReferenceCalculation(BLA::Matrix<3> originalAccel) {
	double pitch; //�����Ǧ�
	double yaw; //ƫ���Ǧ�
	double roll; //��ת�Ǧ�

	//Calculate the reference angle from accelration
	//Ref: http://www.bspilot.com/?p=121
	pitch = atan(originalAccel(1) / sqrt(pow(originalAccel(2), 2) + pow(originalAccel(3), 2)))*(180 / PI);
	yaw = atan(originalAccel(2) / sqrt(pow(originalAccel(1), 2) + pow(originalAccel(3), 2)))*(180 / PI);
	roll = atan(sqrt(pow(originalAccel(1), 2) + pow(originalAccel(2), 2))/originalAccel(1))*(180 / PI);

	BLA::Matrix<3> result = { pitch,yaw,roll };
	BLA::Matrix<3> *pointer = &result;
	return pointer;
}
