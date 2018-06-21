#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include "classifier.h"

/**
 * Initializes GNB
 */
GNB::GNB()
{
}

GNB::~GNB() {}

struct extended_state
{
	double s;
	double d;
	double s_dot;
	double d_dot;
	double lane_pos;
	double heading;
};

void GNB::train(vector<vector<double>> data, vector<string> labels)
{
	std::vector<extended_state> keep_data;
	std::vector<extended_state> right_data;
	std::vector<extended_state> left_data;

	/*
		Trains the classifier with N data points and labels.

		INPUTS
		data - array of N observations
		  - Each observation is a tuple with 4 values: s, d, 
		    s_dot and d_dot.
		  - Example : [
			  	[3.5, 0.1, 5.9, -0.02],
			  	[8.0, -0.3, 3.0, 2.2],
			  	...
		  	]

		labels - array of N labels
		  - Each label is one of "left", "keep", or "right".
	*/
	for (int i = 0; i < data.size(); i++)
	{
		std::string test_label = labels.at(i);
		extended_state test_data;
		test_data.s = data[i][0];
		test_data.d = data[i][1];
		test_data.s_dot = data[i][2];
		test_data.d_dot = data[i][3];
		test_data.lane_pos=lane_position(data[i][0]);
		test_data.heading=heading(data[i][2],data[i][3]);


		if (test_label == "keep")
		{
			keep_data.push_back(test_data);
		}
		if (test_label == "left")
		{
			left_data.push_back(test_data);
		}
		if (test_label == "right")
		{
			right_data.push_back(test_data);
		}
	}
}

string GNB::predict(vector<double> sample)
{
	/*
		Once trained, this method is called and expected to return 
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		# TODO - complete this
	*/

	return this->possible_labels[1];
}

double GNB::lane_position(double d)
{
	// bump total d value up by 2 to provide clean mod by 4;
	double road_pos = d + 2.0;
	// mod by 4 and re-center;
	double lane_pos = fmod(road_pos, 4.0) - 2.0;
	return lane_pos;
}

double GNB::heading(double s_dot, double d_dot)
{
	return atan2(d_dot, s_dot);
}
