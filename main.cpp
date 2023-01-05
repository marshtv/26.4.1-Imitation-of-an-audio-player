#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

class Track {
	private:
		std::string name;
		std::tm created_date;
		int duration = 0;
		bool bIsPlaying = false;
		bool bIsPaused = false;
	public:
		std::string getName() {
			return name;
		}

		std::tm getCreatedDate() {
			return created_date;
		}

		int getDuration() {
			return duration;
		}

		bool getIsPlaying() {
			return bIsPlaying;
		}

		bool getIsPaused() {
			return bIsPaused;
		}

		void setName(std::string* setName) {
			name.resize(setName->size());
			name = *setName;
		}

		void setCreatedDate(std::tm* date) {
			created_date = *date;
		}

		void setDuration(int* duration_in) {
			duration = *duration_in;
		}

		void playTrack() {
			if (!bIsPlaying && !bIsPaused) {
				std::cout << "Track is PLAYING." << std::endl;
				bIsPlaying = true;
				showInfo();
			}
		}

		void pauseTrack() {
			if (bIsPlaying && !bIsPaused) {
				bIsPlaying = false;
				bIsPaused = true;
				std::cout << "Track " << name << " is PAUSED." << std::endl;
			}
		}

		void stopTrack() {
			if (bIsPlaying || bIsPaused) {
				bIsPlaying = false;
				bIsPaused = false;
				std::cout << "Track " << name << " is STOPPED." << std::endl;
			}
		}

		void showInfo() {
			std::cout << "Track name: " << name << std::endl;
			std::cout << "Created Date: " << std::put_time(&created_date, "%d %B %Y %H:%M:%S")<< std::endl;
			std::cout << "Duration: ";
			if (duration / 3600 > 0) {
				std::cout << duration / 3600 << "h ";
				std::cout << (duration % 3600) / 60 << "m ";
				std::cout << (duration % 3600) % 60 << "s." << std::endl;
			} else if (duration / 60 > 0) {
				 std::cout << duration / 60 << "m ";
				 std::cout << duration % 60 << "s." << std::endl;
			} else {
				std::cout << duration << "s." << std::endl;
			}
		}
};

class AudioPlayer {
	private:
		std::vector<Track*> tracks;

	public:


};

int main() {
	Track* track_1 = new Track;

	std::string in_name = "Baby";
	track_1->setName(&in_name);

	std::time_t timeNow = std::time(nullptr);
	std::tm in_time = *std::localtime(&timeNow);
	track_1->setCreatedDate(&in_time);

	int in_duration = 4890;
	track_1->setDuration(&in_duration);

	track_1->showInfo();

	delete track_1;
	track_1 = nullptr;

	return 0;
}
