#ifndef _RUBICKSCUBE_HPP_
#define _RUBICKSCUBE_HPP_

#include <vector>
#include <iostream>

class RubicksCube
{
 private:
	std::vector<std::vector<int>> edges;

	std::vector<int> rotateSideLeft(std::vector<int> s) const
	{
		std::vector<int> buf(9);
		buf[0] = s[2];
		buf[1] = s[5];
		buf[2] = s[8];
		buf[3] = s[1];
		buf[4] = s[4];
		buf[5] = s[7];
		buf[6] = s[0];
		buf[7] = s[3];
		buf[8] = s[6];

		return buf;
	}

	std::vector<int> rotateSideRight(std::vector<int> s) const
	{
		std::vector<int> buf(9);
		buf[0] = s[6];
		buf[1] = s[3];
		buf[2] = s[0];
		buf[3] = s[7];
		buf[4] = s[4];
		buf[5] = s[1];
		buf[6] = s[8];
		buf[7] = s[5];
		buf[8] = s[2];

		return buf;
	}

 public:
	explicit RubicksCube()
	{
		/*
		 * 0 - Top
		 * 1 - Left
		 * 2 - Front
		 * 3 - Right
		 * 4 - Back
		 * 5 - Bottom
		 */
		for (int i = 0; i < 6; i++)
		{
			std::vector<int> edge;
			for (int j = 0; j < 9; j++)
				edge.push_back(i);

			edges.push_back(edge);
		}
		//edges[5][0] = 8;
	}

	void show() const
	{
		std::cout << "\n-----------------------\n\n";

		std::cout << "      " << edges[0][0] << " " << edges[0][1] << " " << edges[0][2] << "\n";
		std::cout << "      " << edges[0][3] << " " << edges[0][4] << " " << edges[0][5] << "\n";
		std::cout << "      " << edges[0][6] << " " << edges[0][7] << " " << edges[0][8] << "\n";

		std::cout << edges[1][0] << " " << edges[1][1] << " " << edges[1][2] << " ";
		std::cout << edges[2][0] << " " << edges[2][1] << " " << edges[2][2] << " ";
		std::cout << edges[3][0] << " " << edges[3][1] << " " << edges[3][2] << " ";
		std::cout << edges[4][0] << " " << edges[4][1] << " " << edges[4][2] << "\n";

		std::cout << edges[1][3] << " " << edges[1][4] << " " << edges[1][5] << " ";
		std::cout << edges[2][3] << " " << edges[2][4] << " " << edges[2][5] << " ";
		std::cout << edges[3][3] << " " << edges[3][4] << " " << edges[3][5] << " ";
		std::cout << edges[4][3] << " " << edges[4][4] << " " << edges[4][5] << "\n";

		std::cout << edges[1][6] << " " << edges[1][7] << " " << edges[1][8] << " ";
		std::cout << edges[2][6] << " " << edges[2][7] << " " << edges[2][8] << " ";
		std::cout << edges[3][6] << " " << edges[3][7] << " " << edges[3][8] << " ";
		std::cout << edges[4][6] << " " << edges[4][7] << " " << edges[4][8] << "\n";

		std::cout << "      " << edges[5][0] << " " << edges[5][1] << " " << edges[5][2] << "\n";
		std::cout << "      " << edges[5][3] << " " << edges[5][4] << " " << edges[5][5] << "\n";
		std::cout << "      " << edges[5][6] << " " << edges[5][7] << " " << edges[5][8] << "\n";

	}


	void R()
	{
		std::vector<int> buf = edges[2];

		edges[2][2] = edges[5][2];
		edges[2][5] = edges[5][5];
		edges[2][8] = edges[5][8];

		edges[5][2] = edges[4][6];
		edges[5][5] = edges[4][3];
		edges[5][8] = edges[4][0];

		edges[4][6] = edges[0][2];
		edges[4][3] = edges[0][5];
		edges[4][0] = edges[0][8];

		edges[0][2] = buf[2];
		edges[0][5] = buf[5];
		edges[0][8] = buf[8];

		edges[3] = rotateSideRight(edges[3]);
	}

	void Rr()
	{
		std::vector<int> buf = edges[2];

		edges[2][2] = edges[0][2];
		edges[2][5] = edges[0][5];
		edges[2][8] = edges[0][8];

		edges[0][2] = edges[4][6];
		edges[0][5] = edges[4][3];
		edges[0][8] = edges[4][0];

		edges[4][6] = edges[5][2];
		edges[4][3] = edges[5][5];
		edges[4][0] = edges[5][8];

		edges[5][2] = buf[2];
		edges[5][5] = buf[5];
		edges[5][8] = buf[8];

		edges[3] = rotateSideLeft(edges[3]);
	}

	void L()
	{
		std::vector<int> buf = edges[2];

		edges[2][0] = edges[0][0];
		edges[2][3] = edges[0][3];
		edges[2][6] = edges[0][6];

		edges[0][0] = edges[4][8];
		edges[0][3] = edges[4][5];
		edges[0][6] = edges[4][2];

		edges[4][8] = edges[5][0];
		edges[4][5] = edges[5][3];
		edges[4][2] = edges[5][6];

		edges[5][0] = buf[0];
		edges[5][3] = buf[3];
		edges[5][6] = buf[6];

		edges[1] = rotateSideRight(edges[1]);
	}

	void Lr()
	{
		std::vector<int> buf = edges[2];

		edges[2][0] = edges[5][0];
		edges[2][3] = edges[5][3];
		edges[2][6] = edges[5][6];

		edges[5][0] = edges[4][8];
		edges[5][3] = edges[4][5];
		edges[5][6] = edges[4][2];

		edges[4][8] = edges[0][0];
		edges[4][5] = edges[0][3];
		edges[4][2] = edges[0][6];

		edges[0][0] = buf[0];
		edges[0][3] = buf[3];
		edges[0][6] = buf[6];

		edges[1] = rotateSideLeft(edges[1]);
	}

	void U()
	{
		std::vector<int> buf = edges[2];

		edges[2][0] = edges[3][0];
		edges[2][1] = edges[3][1];
		edges[2][2] = edges[3][2];

		edges[3][0] = edges[4][0];
		edges[3][1] = edges[4][1];
		edges[3][2] = edges[4][2];

		edges[4][0] = edges[1][0];
		edges[4][1] = edges[1][1];
		edges[4][2] = edges[1][2];

		edges[1][0] = buf[0];
		edges[1][1] = buf[1];
		edges[1][2] = buf[2];

		edges[0] = rotateSideRight(edges[0]);
	}

	void Ur()
	{
		std::vector<int> buf = edges[2];

		edges[2][0] = edges[1][0];
		edges[2][1] = edges[1][1];
		edges[2][2] = edges[1][2];

		edges[1][0] = edges[4][0];
		edges[1][1] = edges[4][1];
		edges[1][2] = edges[4][2];

		edges[4][0] = edges[3][0];
		edges[4][1] = edges[3][1];
		edges[4][2] = edges[3][2];

		edges[3][0] = buf[0];
		edges[3][1] = buf[1];
		edges[3][2] = buf[2];

		edges[0] = rotateSideLeft(edges[0]);
	}

	void D()
	{
		std::vector<int> buf = edges[2];

		edges[2][6] = edges[3][6];
		edges[2][7] = edges[3][7];
		edges[2][8] = edges[3][8];

		edges[3][6] = edges[4][6];
		edges[3][7] = edges[4][7];
		edges[3][8] = edges[4][8];

		edges[4][6] = edges[1][6];
		edges[4][7] = edges[1][7];
		edges[4][8] = edges[1][8];

		edges[1][6] = buf[6];
		edges[1][7] = buf[7];
		edges[1][8] = buf[8];

		edges[5] = rotateSideRight(edges[5]);
	}

	void Dr()
	{
		std::vector<int> buf = edges[2];

		edges[2][6] = edges[1][6];
		edges[2][7] = edges[1][7];
		edges[2][8] = edges[1][8];

		edges[1][6] = edges[4][6];
		edges[1][7] = edges[4][7];
		edges[1][8] = edges[4][8];

		edges[4][6] = edges[3][6];
		edges[4][7] = edges[3][7];
		edges[4][8] = edges[3][8];

		edges[3][6] = buf[6];
		edges[3][7] = buf[7];
		edges[3][8] = buf[8];

		edges[5] = rotateSideLeft(edges[5]);
	}

	//fixed previous backside rotations

	void F()
	{
		std::vector<int> buf = edges[3];

		edges[3][0] = edges[0][6];
		edges[3][3] = edges[0][7];
		edges[3][6] = edges[0][8];

		edges[0][6] = edges[1][8];
		edges[0][7] = edges[1][5];
		edges[0][8] = edges[1][2];

		edges[1][8] = edges[5][2];
		edges[1][5] = edges[5][1];
		edges[1][2] = edges[5][0];

		edges[5][2] = buf[0];
		edges[5][1] = buf[3];
		edges[5][0] = buf[6];

		edges[2] = rotateSideRight(edges[2]);
	}

	void Fr()
	{
		std::vector<int> buf = edges[3];

		edges[3][0] = edges[5][2];
		edges[3][3] = edges[5][1];
		edges[3][6] = edges[5][0];

		edges[5][2] = edges[1][8];
		edges[5][1] = edges[1][5];
		edges[5][0] = edges[1][2];

		edges[1][8] = edges[0][6];
		edges[1][5] = edges[0][7];
		edges[1][2] = edges[0][8];

		edges[0][6] = buf[0];
		edges[0][7] = buf[3];
		edges[0][8] = buf[6];

		edges[2] = rotateSideLeft(edges[2]);
	}

	void B()
	{
		std::vector<int> buf = edges[3];

		edges[3][2] = edges[5][8];
		edges[3][5] = edges[5][7];
		edges[3][8] = edges[5][6];

		edges[5][8] = edges[1][6];
		edges[5][7] = edges[1][3];
		edges[5][6] = edges[1][0];

		edges[1][6] = edges[0][0];
		edges[1][3] = edges[0][1];
		edges[1][0] = edges[0][2];

		edges[0][0] = buf[2];
		edges[0][1] = buf[5];
		edges[0][2] = buf[8];

		edges[4] = rotateSideRight(edges[4]);
	}

	void Br()
	{
		std::vector<int> buf = edges[3];

		edges[3][2] = edges[0][0];
		edges[3][5] = edges[0][1];
		edges[3][8] = edges[0][2];

		edges[0][0] = edges[1][6];
		edges[0][1] = edges[1][3];
		edges[0][2] = edges[1][0];

		edges[1][6] = edges[5][8];
		edges[1][3] = edges[5][7];
		edges[1][0] = edges[5][6];

		edges[5][8] = buf[2];
		edges[5][7] = buf[5];
		edges[5][6] = buf[8];

		edges[4] = rotateSideLeft(edges[4]);
	}
};

#endif //_RUBICKSCUBE_HPP_
