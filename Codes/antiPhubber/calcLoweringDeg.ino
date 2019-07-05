float calcLoweringDeg (float initAccel[3],float currentAccel[3])
{
  float dot = (initAccel[0] * currentAccel[0]) + (initAccel[1] * currentAccel[1]) + (initAccel[2] * currentAccel[2]);
  float mod1 = sqrt(initAccel[0]* initAccel[0]+ initAccel[1]* initAccel[1]+ initAccel[2]* initAccel[2]);
  float mod2 = sqrt(currentAccel[0]* currentAccel[0]+ currentAccel[1] * currentAccel[1]+currentAccel[2] * currentAccel[2]);
  float rslt = acos(dot / (mod1*mod2))*(180/3.141592);

  if (rslt<0)
  {
    rslt = -1 * rslt;
    return rslt;
  }
  else
  {
    return rslt;
  }
}
