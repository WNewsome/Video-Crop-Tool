// Walter Newsome Aug, 2020
// Big thanks to Shermal Fernando and his OpenCV tutorial
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// User input original video and area to be cropped
	int x = 688;
	int y = 262;
	int frame_width = 458;
	int frame_height = 383;
	String video_name = "video.mp4";

	Rect crop_area(x, y, frame_width, frame_height);
	String cropped_video_name = "cropped " + video_name;
	Mat crop_frame;
	String window_name = "cropped video";
	VideoCapture video(video_name);

	if (video.isOpened() == false)
	{
		cout << "Cannot open the video file" << endl;
		cin.get();
		return -1;
	}
	Size frame_size(frame_width, frame_height);
	double fps = video.get(CAP_PROP_FPS); // Obtain original video frames per second
	VideoWriter oVideoWriter(cropped_video_name, VideoWriter::fourcc('M', 'P', '4', '2'), fps, frame_size, true);
	namedWindow(window_name, WINDOW_NORMAL); // Create window

	while (true)
	{
		Mat frame;
		bool bSuccess = video.read(frame);

		if (bSuccess == false)
		{
			cout << "Done" << endl; // Process completed
			break;
		}

		crop_frame = frame(crop_area);
		imshow(window_name, crop_frame);
		oVideoWriter.write(crop_frame);
		if (waitKey(10) == 27)
		{
			cout << "Esc key pressed." << endl;
			break;
		}
	}
	oVideoWriter.release();
	return 0;

}