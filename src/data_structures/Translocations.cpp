/*
 * Translocations.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: vezzi
 */

#include "Translocations.h"


Translocations::Translocations(uint32_t chromosomesNum) {
	this->chromosomesNum=chromosomesNum;
}



void Translocations::insertConnection(uint32_t chr1, uint32_t pos1, uint32_t chr2, uint32_t pos2) {
	Link connection;
	connection.chr1_start = pos1;
	connection.chr1_end = pos1 + 100;


	connection.chr2_start = pos2;
	connection.chr2_end = pos2 + 100;

	connection.supportingPairs = 1;

	Connections[chr1][chr2].push_back(connection);
}





void Translocations::printConnections() {

	for(uint32_t chr1 = 0; chr1 < chromosomesNum ; chr1++) {
		for(uint32_t chr2 = 0; chr2 < chromosomesNum ; chr2++) {
			cout << "connection between " << chr1 << " and " << chr2 << "\n";
			vector<Link>::iterator it;
			for ( it = Connections[chr1][chr2].begin(); it !=   Connections[chr1][chr2].end(); it++) {
				cout << "(" << it->chr1_start << "," << it->chr2_start << ") -- ";
			}
			cout << "\n";
		}
	}

}

void Translocations::compressConnections(uint32_t chr1, uint32_t chr2) {

	cout << "compressing " << chr1 << " and " << chr2 << "\n";
	vector<Link> temporaryVector;

	vector< pair<uint32_t, uint32_t> > LinksToChr2;
	if(Connections[chr1][chr2].size() < 1) {
		return;
	} else {
		Link newLink = Connections[chr1][chr2][0];

		pair<uint32_t, uint32_t> chr2_coords;
		chr2_coords.first  = newLink.chr2_start;
		chr2_coords.second = newLink.chr2_end;
		LinksToChr2.push_back(chr2_coords);

		uint32_t currentIndex = 1;
		while(currentIndex < Connections[chr1][chr2].size() ) {
			Link currentLink = Connections[chr1][chr2][currentIndex];
			if(newLink.chr1_end >= currentLink.chr1_start) {
				// extend new link
				newLink.chr1_end =  currentLink.chr1_end;
				newLink.supportingPairs++;
				chr2_coords.first  = currentLink.chr2_start;
				chr2_coords.second = currentLink.chr2_end;
				LinksToChr2.push_back(chr2_coords);
			} else {
				// now process when a gap is found
				if(newLink.supportingPairs >= 10) {
					cout << newLink.chr1_start << " " << newLink.chr1_end << " " << newLink.supportingPairs << "\n";
					vector<pair <uint32_t, uint32_t> >::iterator it;
					for ( it = LinksToChr2.begin(); it !=   LinksToChr2.end(); it++) {
						cout << "(" << it->first << "," << it->second << ") -- ";
					}
					cout << "\n";
				}
				LinksToChr2.clear();
				newLink = currentLink;
				chr2_coords.first  = currentLink.chr2_start;
				chr2_coords.second = currentLink.chr2_end;
				LinksToChr2.push_back(chr2_coords);

			}
			currentIndex ++;


		}
	}


}



void Translocations::initTrans(SamHeader head) {
	uint32_t contigsNumber = 0;
	SamSequenceDictionary sequences  = head.Sequences;

	for(SamSequenceIterator sequence = sequences.Begin() ; sequence != sequences.End(); ++sequence) {
		this->contig2position[sequence->Name] = contigsNumber; // keep track of contig name and position in order to avoid problems when processing two libraries
		this->position2contig[contigsNumber]  = sequence->Name;
		contigsNumber++;
	}
}


bool sortPairs(pair<uint32_t, uint32_t> i, pair<uint32_t, uint32_t>  j) {
	return (i.first < j.first);
}

bool sortLinks(Link i, Link  j) {
	return (i.chr1_start < j.chr1_start);
}




void Translocations::findEvents(ofstream & OutputFileDescriptor, uint32_t chr1, uint32_t chr2, uint32_t minimumPairs, float minCov, float maxCov, uint32_t windowSize, uint32_t windowStep) {

	vector<Link> temporaryVector;
	vector< pair<uint32_t, uint32_t> > LinksToChr2;


	if(Connections[chr1][chr2].size() < 1) {
		return;
	} else {
		// sort connection based on coordinates from chr1
		sort(Connections[chr1][chr2].begin(), Connections[chr1][chr2].end(), sortLinks);

		// use a 4Kbp window (for now fixed) to find events of interest
		uint32_t currentIndex = 0;
		uint32_t upperLimit;

		while(currentIndex < Connections[chr1][chr2].size() ) {
			Link newLink = Connections[chr1][chr2][currentIndex];
			pair<uint32_t, uint32_t> chr2_coords;
			chr2_coords.first  = newLink.chr2_start;
			chr2_coords.second = newLink.chr2_end;
			LinksToChr2.push_back(chr2_coords);
			upperLimit 		= newLink.chr1_start + windowSize;
			uint32_t nextWindowLimit = newLink.chr1_start + windowStep;
			uint32_t counter = currentIndex + 1;
			while(counter < Connections[chr1][chr2].size() and Connections[chr1][chr2][counter].chr1_start <=  upperLimit) {
				Link currentLink = Connections[chr1][chr2][counter];
				newLink.chr1_end =  currentLink.chr1_end;
				newLink.supportingPairs++;
				chr2_coords.first  = currentLink.chr2_start;
				chr2_coords.second = currentLink.chr2_end;
				LinksToChr2.push_back(chr2_coords);
				counter ++;
			}
			// window has been read... now look for links --- counter points at the last witness, while currentIndex points at the first one of the window
			bool search=true;
			uint32_t windowLength = (newLink.chr1_end - newLink.chr1_start +1);
			if(newLink.supportingPairs >= minimumPairs and windowLength > 200) {
				uint32_t tolleratedWindowLength = 1.5*windowLength;

				vector<pair <uint32_t, uint32_t> >::iterator it;
				sort(LinksToChr2.begin(), LinksToChr2.end(), sortPairs);
				uint32_t currentPair = 0;
				while(search and currentPair < LinksToChr2.size()) {
					uint32_t startAt = LinksToChr2[currentPair].first;
					uint32_t stopAt = LinksToChr2[currentPair].first + tolleratedWindowLength;
					uint32_t pairsInWindow = 1;
					uint32_t nextPair = currentPair + 1;
					while(nextPair < LinksToChr2.size() and LinksToChr2[nextPair].first < stopAt ) {
						pairsInWindow ++;
						nextPair ++;
					}
					uint32_t secondClusterLength = LinksToChr2[nextPair-1].second - startAt;

					float coverage1 =  (float)(newLink.supportingPairs*100)/(float)(windowLength);
					float coverage2 =  (float)(pairsInWindow*100)/(float)(secondClusterLength);

					//and (coverage1 >= minCov and coverage1 <= maxCov) and (coverage2 >= minCov and coverage2 <= maxCov)
					if( pairsInWindow > 0.9 * newLink.supportingPairs and (coverage1 >= minCov and coverage1 <= maxCov) and (coverage2 >= minCov and coverage2 <= maxCov)) {
						search = false;
						OutputFileDescriptor << position2contig[chr1] << "\t" << newLink.chr1_start  << "\t" << newLink.chr1_end   << "\t" << newLink.supportingPairs << "\t" << coverage1 << "\t";
						OutputFileDescriptor << position2contig[chr2] << "\t" << startAt             << "\t" << LinksToChr2[nextPair-1].second << "\t"  << pairsInWindow          << "\t" << coverage2 <<"\n";

						//cout << "(" << position2contig[chr1] << " , " << position2contig[chr2] << " ) (" << chr1 << " , " << chr2 << ") (" << newLink.chr1_start << " , " << newLink.chr1_end << ")";
						//cout << " (" << startAt << " , " << LinksToChr2[nextPair-1].second << ") ";
						//cout << " (" << coverage1 << " , " << coverage2 << ")" ;
						//cout << " (" << newLink.supportingPairs << " , " << pairsInWindow << ")" << "\n";

					} else {
						currentPair ++;
					}
				}
			}
			LinksToChr2.clear();
			//newLink = currentLink;
			if(search == false) { // if I found a possible link
				currentIndex = counter;
			} else {
				while(currentIndex < Connections[chr1][chr2].size() and Connections[chr1][chr2][currentIndex].chr1_start <=  nextWindowLimit) {
					currentIndex ++;
				}
			}


		}
	}
}

