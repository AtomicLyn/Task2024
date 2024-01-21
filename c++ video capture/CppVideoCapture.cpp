#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cuda::printShortCudaDeviceInfo(0);

    setlocale(LC_ALL, "rus");

    String source_filepath = "G:\\Task2024\\CppVideoCapture\\test.mp4";
    String save_filepath = "G:\\Task2024\\CppVideoCapture\\result.avi";
    VideoCapture cap;
    VideoWriter out;
    cap.open(source_filepath);

    if (!cap.isOpened())
    {
        cout << "Файл не найден." << endl;
        return -1;
    }
    else
    {
        cout << "Обработка файла..." << endl;
    }
   
    double fps = cap.get(CAP_PROP_FPS);
    int frameWidth = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    out.open(save_filepath, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(frameWidth, frameHeight)); 

    string codec = cap.getBackendName();
    int currentFrameNumber = -1;
    while (cap.isOpened()) {
        Mat frame;
        if (cap.read(frame)) {
            currentFrameNumber = static_cast<int>(cap.get(CAP_PROP_POS_FRAMES));

            putText(frame, "resolution: " + to_string(frameWidth) + "x" + to_string(frameHeight), Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 255), 2);
            putText(frame, "codec: " + codec, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 255), 2);
            putText(frame, "frame: " + to_string(currentFrameNumber), Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 255), 2);

            out.write(frame);
            currentFrameNumber++;
        }
        else break;
    }  

    out.release();
    cout << "Файл обработан" << endl;

    return 0;
}
