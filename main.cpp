#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>

class Track {
	private:
		std::string name;
		std::time_t timeNow = std::time(nullptr);
		std::tm created_date = *std::localtime(&timeNow);
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

		void initTrack(std::string name_str, int duration_sec) {
			name.resize(name_str.size());
			name = name_str;
			duration = duration_sec;
		}

		void playTrack() {
			if (!bIsPlaying) {
				std::cout << "Track is PLAYING." << std::endl;
				bIsPlaying = true;
				bIsPaused = false;
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
			std::cout << "Created Date: " << std::put_time(&created_date, "%d %b %Y %H:%M:%S")<< std::endl;
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
		void addTrack(Track** track) {
			tracks.push_back(*track);
		}

		void playTrack(std::string& name_str) {
			if (!tracks.empty()) {
				int count = tracks.size();
				for (int i = 0; i < tracks.size(); i++) {
					if (name_str == tracks[i]->getName())
						tracks[i]->playTrack();
					else
						count--;
				}
				if (count == 0)
					std::cout << "Track's name not exist :(" << std::endl;
			} else
				std::cout << "No tracks exist in player :(" << std::endl;
		}

		void pauseTrack() {
			if (!tracks.empty()) {
				for (int i = 0; i < tracks.size(); i++)
					tracks[i]->pauseTrack();
			} else
				std::cout << "No tracks exist in player :(" << std::endl;
		}

		void stopTrack() {
			if (!tracks.empty()) {
				for (int i = 0; i < tracks.size(); i++)
					tracks[i]->stopTrack();
			} else
				std::cout << "No tracks exist in player :(" << std::endl;
		}

		void nextTrack() {
			if (tracks.size() > 1) {
				std::srand(std::time(nullptr));
				int playing_index, next_index;
				for (int i = 0; i < tracks.size(); i++) {
					if (tracks[i]->getIsPlaying() || tracks[i]->getIsPaused())
						playing_index = i;
				}
				next_index = std::rand() % tracks.size();
				while (next_index == playing_index)
					next_index = std::rand() % tracks.size();
				tracks[next_index]->playTrack();
			} else
				std::cout << "Not enough tracks to play next :(" << std::endl;
		}

		void showTracksList() {
			if (!tracks.empty()) {
				for (int i = 0; i < tracks.size(); i++) {
					std::cout << i << ". ";
					tracks[i]->showInfo();
					std::cout <<  "--------------------------------------" << std::endl;
				}
			} else
				std::cout << "No tracks exist in player :(" << std::endl;
		}
};

void deleteTrackClass(Track* track) {
	delete track;
	track = nullptr;
}

void deleteAudioPlayerClass(AudioPlayer* player) {
	delete player;
	player = nullptr;
}

std::string inputCheckCommand() {
	std::string in_str;
	std::cout << "Input command:";
	std::cin >> in_str;
	while ( in_str != "list" && in_str != "play" && in_str != "pause" &&
			in_str != "next" && in_str != "stop" && in_str != "exit") {
		std::cout << "Input command:";
		std::cin >> in_str;
	}
	return in_str;
}

int main() {
	AudioPlayer* audioPlayer = new AudioPlayer;

	Track* track_01 = new Track;
	track_01->initTrack("Baby", 250);
	audioPlayer->addTrack(&track_01);

	Track* track_02 = new Track;
	track_02->initTrack("Human", 235);
	audioPlayer->addTrack(&track_02);

	Track* track_03 = new Track;
	track_03->initTrack("Earth", 230);
	audioPlayer->addTrack(&track_03);

	std::cout << "Hello, tracks was loaded to audio player." << std::endl;
	std::cout << "You have commands to operate audio player:" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "list . . . for display existing tracks in audio player," << std::endl;
	std::cout << "play . . . for select track's name and play track," << std::endl;
	std::cout << "pause. . . for stay to pause the playing track," << std::endl;
	std::cout << "next . . . for change the playing track," << std::endl;
	std::cout << "stop . . . for stop the playing track," << std::endl;
	std::cout << "exit . . . for exit program." << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	while (true) {
		std::string command = inputCheckCommand();
		if (command == "list") {
			std::cout << "-------------------------------------------------------" << std::endl;
			audioPlayer->showTracksList();
		}
		else if (command == "play") {
			std::string name_str;
			std::cout << "Input track's name to start playing it:";
			std::cin >> name_str;
			std::cout << "-------------------------------------------------------" << std::endl;
			audioPlayer->playTrack(name_str);
		} else if (command == "pause")
			audioPlayer->pauseTrack();
		else if (command == "next") {
			std::cout << "-------------------------------------------------------" << std::endl;
			audioPlayer->nextTrack();
		}
		else if (command == "stop") {
			audioPlayer->stopTrack();
			std::cout << "-------------------------------------------------------" << std::endl;
		}
		else if (command == "exit")
			break;
	}

	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "Exit from Audio Player. Good by." << std::endl;

	deleteAudioPlayerClass(audioPlayer);
	deleteTrackClass(track_01);
	deleteTrackClass(track_02);
	deleteTrackClass(track_03);
	return 0;
}
