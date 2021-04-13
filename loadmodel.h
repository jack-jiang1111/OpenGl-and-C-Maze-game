#include <stdio.h>
#include <ctype.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

float* read_obj(const char* filename, int& lines)
{
	FILE* file = fopen(filename,"r");
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	while (1)
	{
		
		char header[128];
		int line = fscanf(file, "%s", header);
		if (line == EOF)
		{
			break;
		}
		if (strcmp(header, "#") == 0)
		{
			char trash[128];
			std::fgets(trash,128,file);
		}
		else if (strcmp(header, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(header, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(header, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(header, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				break;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	
	int num_lines = vertexIndices.size()  +uvIndices.size() + normalIndices.size();
	int num_vert = vertexIndices.size() / 3;
	float* model = new float[num_lines];
	int index = 0;

	// cout << "end" << endl;
	// copy model data into model array
	for (int i = 0; i < num_vert; i++)
	{
		//cout << i << endl;
		model[index] = vertexIndices[3*i];
		model[index+1] = vertexIndices[3*i+1];
		model[index+2] = vertexIndices[3*i+2];

		model[index + 3] = uvIndices[2*i];
		model[index + 4] = uvIndices[2*i + 1];

		model[index + 5] = normalIndices[3*i];
		model[index + 6] = normalIndices[3*i + 1];
		model[index + 7] = normalIndices[3*i + 2];

		index += 8;
	}
	for (int i = 0; i < num_lines; i++)
	{
		//cout << model[i] << endl;
	}
	lines = num_lines;
	return model;
	
}