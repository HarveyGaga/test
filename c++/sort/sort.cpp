void CameraSort(connectbody body[], int size)
{
	int i, j, k;
	connectbody temp;
	char tempBerthCode[50];

	for(i = 0; i < size-1; i++)
	{
		for(j = i+1; j < size; j++)
		{
			if(strcmp(body[j].IP, body[i].IP) < 0)
			{
				memcpy(&temp, &body[i], sizeof(connectbody)-sizeof(XunjianImageStr)*5);
				memcpy(&body[i], &body[j], sizeof(connectbody)-sizeof(XunjianImageStr)*5);
				memcpy(&body[j], &temp, sizeof(connectbody)-sizeof(XunjianImageStr)*5);
				for(k = 0; k < 5; k++)
				{
					memcpy(tempBerthCode, body[i].xunjianPic[k].berthCode, 50);
					memcpy(body[i].xunjianPic[k].berthCode, body[j].xunjianPic[k].berthCode, 50);
					memcpy(body[j].xunjianPic[k].berthCode, tempBerthCode, 50);
				}
			}
		}
	}
}

