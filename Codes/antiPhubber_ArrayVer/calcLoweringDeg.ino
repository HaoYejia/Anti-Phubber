float calcLoweringDeg (float initAccel[3],float currentAccel[3])
{
  float dotMultiply = initAccel[0]*currentAccel[0]+initAccel[1]*currentAccel[1]+initAccel[2]*currentAccel[2];
  float modulusInitVec = sqrt(initAccel[0]*initAccel[0]+initAccel[1]*initAccel[1]+initAccel[2]*initAccel[2]);
  float modulusCurrentVec = sqrt(currentAccel[0]*currentAccel[0]+currentAccel[1]*currentAccel[1]+currentAccel[2]*currentAccel[2]);
  float rslt = dotMultiply/(modulusInitVec + modulusCurrentVec);

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
