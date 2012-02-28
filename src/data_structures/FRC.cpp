/*
 * FRC.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: vezzi
 */

#include "FRC.h"


bool sortContigs(contigFeatures i, contigFeatures j) {
	return (i.getContigLength() > j.getContigLength());
}

FRC::FRC() {

}

FRC::~FRC() {
	if (CONTIG.empty() != 0) {
		CONTIG.~vector();
	}
}

FRC::FRC(unsigned int contigs) {
	this->contigs = contigs;
	this->CONTIG.resize(contigs);
}


void FRC::sortFRC() {
	sort(CONTIG.begin(), CONTIG.end(), sortContigs);
}


void FRC::setContigLength(unsigned int ctg, unsigned int contigLength) {
	CONTIG[ctg].setContigLength(contigLength);
}

unsigned int FRC::getContigLength(unsigned int ctg) {
	return this->CONTIG[ctg].getContigLength();
}

unsigned int FRC::getFeature(unsigned int ctg, Feature f) {
	switch(f) {
	case LOW_COVERAGE_AREA: return  this->CONTIG[ctg].getLOW_COVERAGE_AREA(); break;
	case HIGH_COVERAGE_AREA: return  this->CONTIG[ctg].getHIGH_COVERAGE_AREA() ; break;
	case LOW_NORMAL_AREA: return this->CONTIG[ctg].getLOW_NORMAL_AREA(); break;
	case HIGH_NORMAL_AREA:return  this->CONTIG[ctg].getHIGH_NORMAL_AREA(); break;
	case HIGH_SINGLE_AREA: return this->CONTIG[ctg].getHIGH_SINGLE_AREA() ; break;
	case HIGH_SPANNING_AREA: return this->CONTIG[ctg].getHIGH_SPANNING_AREA() ; break;
	case HIGH_OUTIE_AREA: return this->CONTIG[ctg].getHIGH_OUTIE_AREA() ; break;
	case COMPRESSION_AREA: return this->CONTIG[ctg].getCOMPRESSION_AREA() ; break;
	case STRECH_AREA: return this->CONTIG[ctg].getSTRECH_AREA() ; break;
	case TOTAL: return this->CONTIG[ctg].getTOTAL(); break;
	default: cout << f << "undefined feature, exit with error\n"; return 100;
	}
	return 100;
}




void FRC::setFeature(unsigned int ctg, Feature f, unsigned int value) {
	switch(f) {
	case LOW_COVERAGE_AREA:   this->CONTIG[ctg].setLOW_COVERAGE_AREA(value); break;
	case HIGH_COVERAGE_AREA: this->CONTIG[ctg].setHIGH_COVERAGE_AREA(value) ; break;
	case LOW_NORMAL_AREA: this->CONTIG[ctg].setLOW_NORMAL_AREA(value); break;
	case HIGH_NORMAL_AREA:  this->CONTIG[ctg].setHIGH_NORMAL_AREA(value); break;
	case HIGH_SINGLE_AREA: this->CONTIG[ctg].setHIGH_SINGLE_AREA(value) ; break;
	case HIGH_SPANNING_AREA: this->CONTIG[ctg].setHIGH_SPANNING_AREA(value) ; break;
	case HIGH_OUTIE_AREA:  this->CONTIG[ctg].setHIGH_OUTIE_AREA(value) ; break;
	case COMPRESSION_AREA: this->CONTIG[ctg].setCOMPRESSION_AREA(value) ; break;
	case STRECH_AREA:  this->CONTIG[ctg].setSTRECH_AREA(value) ; break;
	case TOTAL: this->CONTIG[ctg].setTOTAL(value); break;
	default: cout << f << "undefined feature, exit with error\n";;
	}
}

void FRC::computeLowCoverageArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getLowCoverageAreasZones(this->C_A);
	this->CONTIG[ctg].updateLOW_COVERAGE_AREA(feat);
	for(unsigned int i=0; i< contig->lowCoverageAreas.size(); i++) {
		this->CONTIG[ctg].LOW_COVERAGE_AREAS.push_back(contig->lowCoverageAreas.at(i));
	}

//	unsigned int lowCoverageFeatures = contig->getLowCoverageAreas(this->C_A);
//	this->CONTIG[ctg].updateLOW_COVERAGE_AREA(lowCoverageFeatures);
}

void FRC::computeHighCoverageArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getHighCoverageAreasZones(this->C_A);
	this->CONTIG[ctg].updateHIGH_COVERAGE_AREA(feat);
	for(unsigned int i=0; i< contig->highCoverageAreas.size(); i++) {
		this->CONTIG[ctg].HIGH_COVERAGE_AREAS.push_back(contig->highCoverageAreas.at(i));
	}

//	unsigned int highCoverageFeatures = contig->getHighCoverageAreas(this->C_A);
//	this->CONTIG[ctg].updateHIGH_COVERAGE_AREA(highCoverageFeatures);
}

void FRC::computeLowNormalArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getLowNormalAreasZones(this->C_M);
	this->CONTIG[ctg].updateLOW_NORMAL_AREA(feat);
	for(unsigned int i=0; i < contig->lowNormalAreas.size(); i++) {
		this->CONTIG[ctg].LOW_NORMAL_AREAS.push_back(contig->lowNormalAreas.at(i) );
	}
//	unsigned int lowNormalFeatures = contig->getLowNormalAreas(this->C_M);
//	this->CONTIG[ctg].updateLOW_NORMAL_AREA(lowNormalFeatures);
}

void FRC::computeHighNormalArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getHighNormalAreasZones(this->C_M);
	this->CONTIG[ctg].updateHIGH_NORMAL_AREA(feat);
	for(unsigned int i=0; i< contig->highNormalAreas.size(); i++) {
		this->CONTIG[ctg].HIGH_NORMAL_AREAS.push_back(contig->highNormalAreas.at(i));
	}
//	unsigned int highNormalFeatures = contig->getHighNormalAreas(this->C_M);
//	this->CONTIG[ctg].updateHIGH_NORMAL_AREA(highNormalFeatures);

}

void FRC::computeHighSingleArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getHighSingleAreasZones();
	this->CONTIG[ctg].updateHIGH_SINGLE_AREA(feat);
	for(unsigned int i=0; i< contig->highSingleAreas.size(); i++) {
		this->CONTIG[ctg].HIGH_SINGLE_AREAS.push_back(contig->highSingleAreas.at(i));
	}
//	unsigned int highSingleFeatures = contig->getHighSingleAreas();
//	this->CONTIG[ctg].updateHIGH_SINGLE_AREA(highSingleFeatures);
}

void FRC::computeHighSpanningArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getHighSpanningAreasZones();
	this->CONTIG[ctg].updateHIGH_SPANNING_AREA(feat);
	for(unsigned int i=0; i< contig->highSpanningAreas.size(); i++) {
		this->CONTIG[ctg].HIGH_SPANNING_AREAS.push_back(contig->highSpanningAreas.at(i));
	}
//	unsigned int highSpanningFeatures = contig->getHighSpanningAreas();
//	this->CONTIG[ctg].updateHIGH_SPANNING_AREA(highSpanningFeatures);
}

void FRC::computeHighOutieArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getHighOutieAreasZones();
	this->CONTIG[ctg].updateHIGH_OUTIE_AREA(feat);
	for(unsigned int i=0; i < contig->highOutieAreas.size(); i++) {
		this->CONTIG[ctg].HIGH_OUTIE_AREAS.push_back(contig->highOutieAreas.at(i));
	}
//	unsigned int highOutieFeatures = contig->getHighOutieAreas();
//	this->CONTIG[ctg].updateHIGH_OUTIE_AREA(highOutieFeatures);

}

void FRC::computeCompressionArea(unsigned int ctg, Contig *contig) {
	//cout << "library " << this->insertMean << " " << this->insertStd << "\n";
	unsigned int feat = contig->getCompressionAreasZones(this->insertMean, this->insertStd);
	this->CONTIG[ctg].updateCOMPRESSION_AREA(feat);
	for(unsigned int i=0; i< contig->compressionAreas.size(); i++) {
		this->CONTIG[ctg].COMPRESSION_AREAS.push_back(contig->compressionAreas.at(i));
	}
//	unsigned int compressionFeatures = contig->getCompressionAreas(this->insertMean, this->insertStd);
//	this->CONTIG[ctg].updateCOMPRESSION_AREA(compressionFeatures);

}

void FRC::computeStrechArea(unsigned int ctg, Contig *contig) {
	unsigned int feat = contig->getExpansionAreasZones(this->insertMean, this->insertStd);
	this->CONTIG[ctg].updateSTRECH_AREA(feat);
	for(unsigned int i=0; i < contig->expansionAreas.size(); i++) {
		this->CONTIG[ctg].STRECH_AREAS.push_back(contig->expansionAreas.at(i));
	}
//	unsigned int expansionFeatures = contig->getExpansionAreas(this->insertMean, this->insertStd);
//	this->CONTIG[ctg].updateSTRECH_AREA(expansionFeatures);
}

void FRC::computeTOTAL(unsigned int ctg) {
	this->CONTIG[ctg].computeTOTAL();
}



void FRC::setC_A(float C_A) {
	this->C_A = C_A;
}
void FRC::setS_A(float S_A) {
	this->S_A = S_A;
}
void FRC::setC_M(float C_M) {
	this->C_M = C_M;
}
void FRC::setC_W(float C_W) {
	this->C_W = C_W;
}
void FRC::setC_S(float C_S) {
	this->C_S = C_S;
}
void FRC::setC_C(float C_C) {
	this->C_C = C_C;
}
void FRC::setInsertMean(float insertMean) {
	this->insertMean = insertMean;
}
void FRC::setInsertStd(float insertStd) {
	this->insertStd = insertStd;
}

void FRC::setID(unsigned int i, string ID) {
	CONTIG[i].setID(ID);
}

string  FRC::getID(unsigned int i) {
	return CONTIG[i].getID();
}


void FRC::setUpContigs() {
	for(unsigned int i=0; i < this->contigs; i++) {
		this->CONTIG[i].setUpContig();
	}

}


void FRC::printContig(unsigned int ctg) {
	CONTIG[ctg].print();
}

void FRC::printFeatures(unsigned int ctg, ofstream &file) {
	this->CONTIG[ctg].printFeatures(file);

}




contigFeatures::contigFeatures() {
	contigLength = 0;
	LOW_COVERAGE_AREA = 0;
	HIGH_COVERAGE_AREA = 0;
	LOW_NORMAL_AREA = 0;
	HIGH_NORMAL_AREA = 0;
	HIGH_SINGLE_AREA = 0;
	HIGH_SPANNING_AREA = 0;
	HIGH_OUTIE_AREA = 0;
	COMPRESSION_AREA = 0;
	STRECH_AREA = 0;
	TOTAL = 0;


	LOW_COVERAGE_AREAS.clear();
	HIGH_COVERAGE_AREAS.clear();;
	LOW_NORMAL_AREAS.clear();;
	HIGH_NORMAL_AREAS.clear();;
	HIGH_SINGLE_AREAS.clear();;
	HIGH_SPANNING_AREAS.clear();;
	HIGH_OUTIE_AREAS.clear();;
	COMPRESSION_AREAS.clear();;
	STRECH_AREAS.clear();;
	TOTAL_AREAS.clear();;
}

contigFeatures::~contigFeatures() {

}


unsigned long int contigFeatures::getContigLength() {
	return this->contigLength;
}

void contigFeatures::setContigLength(unsigned int contigLength) {
	this->contigLength = contigLength;
}

void contigFeatures::setLOW_COVERAGE_AREA(unsigned int numFeat) {
	this->LOW_COVERAGE_AREA = numFeat;
}
void contigFeatures::setHIGH_COVERAGE_AREA(unsigned int numFeat) {
	this->HIGH_COVERAGE_AREA = numFeat;
}
void contigFeatures::setLOW_NORMAL_AREA(unsigned int numFeat) {
	this->LOW_NORMAL_AREA = numFeat;
}
void contigFeatures::setHIGH_NORMAL_AREA(unsigned int numFeat) {
	this->HIGH_NORMAL_AREA = numFeat;
}
void contigFeatures::setHIGH_SINGLE_AREA(unsigned int numFeat) {
	this->HIGH_SINGLE_AREA = numFeat;
}
void contigFeatures::setHIGH_SPANNING_AREA(unsigned int numFeat) {
	this->HIGH_SPANNING_AREA = numFeat;
}
void contigFeatures::setHIGH_OUTIE_AREA(unsigned int numFeat) {
	this->HIGH_OUTIE_AREA = numFeat;
}
void contigFeatures::setCOMPRESSION_AREA(unsigned int numFeat) {
	this->COMPRESSION_AREA = numFeat;
}
void contigFeatures::setSTRECH_AREA(unsigned int numFeat) {
	this->STRECH_AREA = numFeat;
}


void contigFeatures::updateLOW_COVERAGE_AREA(unsigned int numFeat) {
	this->LOW_COVERAGE_AREA += numFeat;
}
void contigFeatures::updateHIGH_COVERAGE_AREA(unsigned int numFeat) {
	this->HIGH_COVERAGE_AREA += numFeat;
}
void contigFeatures::updateLOW_NORMAL_AREA(unsigned int numFeat) {
	this->LOW_NORMAL_AREA += numFeat;
}
void contigFeatures::updateHIGH_NORMAL_AREA(unsigned int numFeat) {
	this->HIGH_NORMAL_AREA += numFeat;
}
void contigFeatures::updateHIGH_SINGLE_AREA(unsigned int numFeat) {
	this->HIGH_SINGLE_AREA += numFeat;
}
void contigFeatures::updateHIGH_SPANNING_AREA(unsigned int numFeat) {
	this->HIGH_SPANNING_AREA += numFeat;
}
void contigFeatures::updateHIGH_OUTIE_AREA(unsigned int numFeat) {
	this->HIGH_OUTIE_AREA += numFeat;
}
void contigFeatures::updateCOMPRESSION_AREA(unsigned int numFeat) {
	this->COMPRESSION_AREA += numFeat;
}
void contigFeatures::updateSTRECH_AREA(unsigned int numFeat) {
	this->STRECH_AREA += numFeat;
}


void contigFeatures::computeTOTAL() {
	this->TOTAL = 	this->LOW_COVERAGE_AREA + this->HIGH_COVERAGE_AREA + this->LOW_NORMAL_AREA + this->HIGH_NORMAL_AREA +
			this->HIGH_SINGLE_AREA + this->HIGH_SPANNING_AREA + this->HIGH_OUTIE_AREA + this->COMPRESSION_AREA + this->STRECH_AREA;
}


void contigFeatures::setTOTAL(unsigned int numFeat) {
	this->STRECH_AREA = numFeat;
}


void contigFeatures::setID(string ID) {
	this->contigID = ID;
}

string contigFeatures::getID() {
	return this->contigID;
}

/*	void updateFeatures(windowStatistics* window) {
		float C_A_i = window->readsLength_win/(float)window->insertsLength_win;
		float S_A_i = window->insertsLength_win/(float)window->insertsLength_win;
		float C_M_i = window->correctlyMatedReadsLength_win/(float)window->insertsLength_win;
		float C_W_i = (window->wronglyDistanceReadsLength_win + window->wronglyOrientedReadsLength_win)/(float)window->insertsLength_win;
		float C_S_i = window->singletonReadsLength_win/(float)window->insertsLength_win;
		float C_C_i = window->matedDifferentContigLength_win/(float)window->insertsLength_win;
	}
 */


unsigned int contigFeatures::getLOW_COVERAGE_AREA() {return LOW_COVERAGE_AREA;}
unsigned int contigFeatures::getHIGH_COVERAGE_AREA() {return HIGH_COVERAGE_AREA;}
unsigned int contigFeatures::getLOW_NORMAL_AREA() {return LOW_NORMAL_AREA;}
unsigned int contigFeatures::getHIGH_NORMAL_AREA() {return HIGH_NORMAL_AREA;}
unsigned int contigFeatures::getHIGH_SINGLE_AREA() {return HIGH_SINGLE_AREA;}
unsigned int contigFeatures::getHIGH_SPANNING_AREA() {return HIGH_SPANNING_AREA;}
unsigned int contigFeatures::getHIGH_OUTIE_AREA() {return HIGH_OUTIE_AREA;}
unsigned int contigFeatures::getCOMPRESSION_AREA() {return COMPRESSION_AREA;}
unsigned int contigFeatures::getSTRECH_AREA() {return STRECH_AREA;}
unsigned int contigFeatures::getTOTAL() {return TOTAL;}

bool sortPairs (pair<unsigned int, unsigned int> i,pair<unsigned int, unsigned int> j) { return (i.first < j.first); }
bool comparePairs (pair<unsigned int, unsigned int> i,pair<unsigned int, unsigned int> j) { return (i.first == j.first && i.second == j.second); }

void contigFeatures::setUpContig() {
	// set up vectors containing features
	vector<pair<unsigned int, unsigned int> >::iterator it;
	vector<pair<unsigned int, unsigned int> > container;
	pair<unsigned int, unsigned int> currentPair;

	if(!this->LOW_COVERAGE_AREAS.empty()) {
		sort(this->LOW_COVERAGE_AREAS.begin(), this->LOW_COVERAGE_AREAS.end(), sortPairs) ;
		it = unique(this->LOW_COVERAGE_AREAS.begin(), this->LOW_COVERAGE_AREAS.end(),comparePairs);
		this->LOW_COVERAGE_AREAS.resize(it - this->LOW_COVERAGE_AREAS.begin());
		currentPair = this->LOW_COVERAGE_AREAS.at(0);
		for(unsigned int i=1; i < this->LOW_COVERAGE_AREAS.size(); i++) {
			if(this->LOW_COVERAGE_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->LOW_COVERAGE_AREAS[i].second) {
					currentPair.second = this->LOW_COVERAGE_AREAS[i].second;// extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->LOW_COVERAGE_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->LOW_COVERAGE_AREAS = container;
	}
	container.clear();


	if(!this->HIGH_COVERAGE_AREAS.empty()) {
		sort(this->HIGH_COVERAGE_AREAS.begin(), this->HIGH_COVERAGE_AREAS.end(), sortPairs) ;
		it = unique(this->HIGH_COVERAGE_AREAS.begin(), this->HIGH_COVERAGE_AREAS.end(),comparePairs);
		this->HIGH_COVERAGE_AREAS.resize(it - this->HIGH_COVERAGE_AREAS.begin());
		currentPair = this->HIGH_COVERAGE_AREAS.at(0);
		for(unsigned int i=1; i < this->HIGH_COVERAGE_AREAS.size(); i++) {
			if(this->HIGH_COVERAGE_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->HIGH_COVERAGE_AREAS[i].second) {
					currentPair.second = this->HIGH_COVERAGE_AREAS[i].second;// extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->HIGH_COVERAGE_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->HIGH_COVERAGE_AREAS = container;
	}
	container.clear();



	if(!this->LOW_NORMAL_AREAS.empty()) {
		sort(this->LOW_NORMAL_AREAS.begin(), this->LOW_NORMAL_AREAS.end(), sortPairs) ;
		it = unique(this->LOW_NORMAL_AREAS.begin(), this->LOW_NORMAL_AREAS.end(),comparePairs);
		this->LOW_NORMAL_AREAS.resize(it - this->LOW_NORMAL_AREAS.begin());
		currentPair = this->LOW_NORMAL_AREAS.at(0);
		for(unsigned int i=1; i < this->LOW_NORMAL_AREAS.size(); i++) {
			if(this->LOW_NORMAL_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->LOW_NORMAL_AREAS[i].second) {
					currentPair.second = this->LOW_NORMAL_AREAS[i].second;// extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->LOW_NORMAL_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->LOW_NORMAL_AREAS = container;
	}
	container.clear();



	if(!this->HIGH_NORMAL_AREAS.empty()) {
		sort(this->HIGH_NORMAL_AREAS.begin(), this->HIGH_NORMAL_AREAS.end(), sortPairs) ;
		it = unique(this->HIGH_NORMAL_AREAS.begin(), this->HIGH_NORMAL_AREAS.end(),comparePairs);
		this->HIGH_NORMAL_AREAS.resize(it - this->HIGH_NORMAL_AREAS.begin());
		currentPair = this->HIGH_NORMAL_AREAS.at(0);
		for(unsigned int i=1; i < this->HIGH_NORMAL_AREAS.size(); i++) {
			if(this->HIGH_NORMAL_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->HIGH_NORMAL_AREAS[i].second) {
					currentPair.second = this->HIGH_NORMAL_AREAS[i].second;// extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->HIGH_NORMAL_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->HIGH_NORMAL_AREAS = container;
	}
	container.clear();



	if(!this->HIGH_SINGLE_AREAS.empty()) {
		sort(this->HIGH_SINGLE_AREAS.begin(), this->HIGH_SINGLE_AREAS.end(), sortPairs) ;
		it = unique(this->HIGH_SINGLE_AREAS.begin(), this->HIGH_SINGLE_AREAS.end(),comparePairs);
		this->HIGH_SINGLE_AREAS.resize(it - this->HIGH_SINGLE_AREAS.begin());
		currentPair = this->HIGH_SINGLE_AREAS.at(0);
		for(unsigned int i=1; i < this->HIGH_SINGLE_AREAS.size(); i++) {
			if(this->HIGH_SINGLE_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->HIGH_SINGLE_AREAS[i].second) {
					currentPair.second = this->HIGH_SINGLE_AREAS[i].second;// extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->HIGH_SINGLE_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->HIGH_SINGLE_AREAS = container;
	}
	container.clear();



	if(!this->HIGH_SPANNING_AREAS.empty()) {
		sort(this->HIGH_SPANNING_AREAS.begin(), this->HIGH_SPANNING_AREAS.end(), sortPairs) ;
		it = unique(this->HIGH_SPANNING_AREAS.begin(), this->HIGH_SPANNING_AREAS.end(),comparePairs);
		this->HIGH_SPANNING_AREAS.resize(it - this->HIGH_SPANNING_AREAS.begin());
		currentPair = this->HIGH_SPANNING_AREAS.at(0);
		for(unsigned int i=1; i < this->HIGH_SPANNING_AREAS.size(); i++) {
			if(this->HIGH_SPANNING_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->HIGH_SPANNING_AREAS[i].second) {
					currentPair.second = this->HIGH_SPANNING_AREAS[i].second; // extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->HIGH_SPANNING_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->HIGH_SPANNING_AREAS = container;
	}
	container.clear();


	if(!this->HIGH_OUTIE_AREAS.empty()) {
		sort(this->HIGH_OUTIE_AREAS.begin(), this->HIGH_OUTIE_AREAS.end(), sortPairs) ;
		it = unique(this->HIGH_OUTIE_AREAS.begin(), this->HIGH_OUTIE_AREAS.end(),comparePairs);
		this->HIGH_OUTIE_AREAS.resize(it - this->HIGH_OUTIE_AREAS.begin());
		currentPair = this->HIGH_OUTIE_AREAS.at(0);
		for(unsigned int i=1; i < this->HIGH_OUTIE_AREAS.size(); i++) {
			if(this->HIGH_OUTIE_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->HIGH_OUTIE_AREAS[i].second) {
					currentPair.second = this->HIGH_OUTIE_AREAS[i].second; // extend if necessary
				}
			} else {
				container.push_back(currentPair);
				currentPair = this->HIGH_OUTIE_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->HIGH_OUTIE_AREAS = container;
	}
	container.clear();



	if(!this->COMPRESSION_AREAS.empty()) {
		sort(this->COMPRESSION_AREAS.begin(), this->COMPRESSION_AREAS.end(), sortPairs) ;
		it = unique(this->COMPRESSION_AREAS.begin(), this->COMPRESSION_AREAS.end(),comparePairs);
		this->COMPRESSION_AREAS.resize(it - this->COMPRESSION_AREAS.begin());
		currentPair = this->COMPRESSION_AREAS.at(0);
		for(unsigned int i=1; i < this->COMPRESSION_AREAS.size(); i++) {
			if(this->COMPRESSION_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->COMPRESSION_AREAS[i].second) {
					currentPair.second = this->COMPRESSION_AREAS[i].second; // extend if necessary
				}

			} else {
				container.push_back(currentPair);
				currentPair = this->COMPRESSION_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->COMPRESSION_AREAS = container;
	}
	container.clear();


	if(!this->STRECH_AREAS.empty()) {
		sort(this->STRECH_AREAS.begin(), this->STRECH_AREAS.end(), sortPairs) ;
		it = unique(this->STRECH_AREAS.begin(), this->STRECH_AREAS.end(),comparePairs);
		this->STRECH_AREAS.resize(it - this->STRECH_AREAS.begin());
		currentPair = this->STRECH_AREAS.at(0);
		for(unsigned int i=1; i < this->STRECH_AREAS.size(); i++) {
			if(this->STRECH_AREAS[i].first < currentPair.second) { // features are overlapping
				if(currentPair.second < this->STRECH_AREAS[i].second) {
					currentPair.second = this->STRECH_AREAS[i].second; // extend if necessary
				}

			} else {
				container.push_back(currentPair);
				currentPair = this->STRECH_AREAS[i];
			}
		}
		container.push_back(currentPair);
		this->STRECH_AREAS = container;
	}
	container.clear();


}


struct ternary{
	string feature;
	unsigned int start;
	unsigned int end;
};


bool sortTernary(ternary t1, ternary t2) {return (t1.start < t2.start);}

void contigFeatures::printFeatures(ofstream &file) {
	vector<ternary> allFeaturesCtg;

	for(unsigned int i=0; i< LOW_COVERAGE_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "LOW_COV";
		tmp.start = LOW_COVERAGE_AREAS.at(i).first;
		tmp.end = LOW_COVERAGE_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< HIGH_COVERAGE_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "HIGH_COV";
		tmp.start = HIGH_COVERAGE_AREAS.at(i).first;
		tmp.end = HIGH_COVERAGE_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< LOW_NORMAL_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "LOW_NORM";
		tmp.start = LOW_NORMAL_AREAS.at(i).first;
		tmp.end = LOW_NORMAL_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< HIGH_NORMAL_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "HIGH_NORM";
		tmp.start = HIGH_NORMAL_AREAS.at(i).first;
		tmp.end = HIGH_NORMAL_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< HIGH_SINGLE_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "HIGH_SINGLE";
		tmp.start = HIGH_SINGLE_AREAS.at(i).first;
		tmp.end = HIGH_SINGLE_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< HIGH_SPANNING_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "HIGH_SPAN";
		tmp.start = HIGH_SPANNING_AREAS.at(i).first;
		tmp.end = HIGH_SPANNING_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< HIGH_OUTIE_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "HIGH_OUTIE";
		tmp.start = HIGH_OUTIE_AREAS.at(i).first;
		tmp.end = HIGH_OUTIE_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< COMPRESSION_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "COMPR";
		tmp.start = COMPRESSION_AREAS.at(i).first;
		tmp.end = COMPRESSION_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}
	for(unsigned int i=0; i< STRECH_AREAS.size(); i++) {
		ternary tmp;
		tmp.feature = "STRECH";
		tmp.start = STRECH_AREAS.at(i).first;
		tmp.end = STRECH_AREAS.at(i).second;
		allFeaturesCtg.push_back(tmp);
	}

	unsigned int total = 0;
	sort(allFeaturesCtg.begin(), allFeaturesCtg.end(), sortTernary);
	for(unsigned int i=0; i < allFeaturesCtg.size(); i++) {
		file << this->contigID << " " << allFeaturesCtg[i].feature << " " << allFeaturesCtg[i].start << " " << allFeaturesCtg[i].end << "\n";
		total += floor((allFeaturesCtg[i].end - allFeaturesCtg[i].start + 1)/(float)1000 + 0.5);
	}
	//this->TOTAL = total;


}


void contigFeatures::print() {
	cout << "contigLength " << contigLength << "\n";
	cout << "LOW_COVERAGE_AREA " << LOW_COVERAGE_AREA << ": ";
	for(unsigned int i = 0; i < this->LOW_COVERAGE_AREAS.size(); i++) {
		cout << "(" << this->LOW_COVERAGE_AREAS[i].first << "," << this->LOW_COVERAGE_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "HIGH_COVERAGE_AREA " << HIGH_COVERAGE_AREA << ": ";
	for(unsigned int i = 0; i < this->HIGH_COVERAGE_AREAS.size(); i++) {
		cout << "(" << this->HIGH_COVERAGE_AREAS[i].first << "," << this->HIGH_COVERAGE_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "LOW_NORMAL_AREA " << LOW_NORMAL_AREA << ": ";
	for(unsigned int i = 0; i < this->LOW_NORMAL_AREAS.size(); i++) {
		cout << "(" << this->LOW_NORMAL_AREAS[i].first << "," << this->LOW_NORMAL_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "HIGH_NORMAL_AREA " << HIGH_NORMAL_AREA << ": ";
	for(unsigned int i = 0; i < this->HIGH_NORMAL_AREAS.size(); i++) {
		cout << "(" << this->HIGH_NORMAL_AREAS[i].first << "," << this->HIGH_NORMAL_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "HIGH_SINGLE_AREA " << HIGH_SINGLE_AREA << ": ";
	for(unsigned int i = 0; i < this->HIGH_SINGLE_AREAS.size(); i++) {
		cout << "(" << this->HIGH_SINGLE_AREAS[i].first << "," << this->HIGH_SINGLE_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "HIGH_SPANNING_AREA " << HIGH_SPANNING_AREA << ": ";
	for(unsigned int i = 0; i < this->HIGH_SPANNING_AREAS.size(); i++) {
		cout << "(" << this->HIGH_SPANNING_AREAS[i].first << "," << this->HIGH_SPANNING_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "HIGH_OUTIE_AREA " << HIGH_OUTIE_AREA << ": ";
	for(unsigned int i = 0; i < this->HIGH_OUTIE_AREAS.size(); i++) {
		cout << "(" << this->HIGH_OUTIE_AREAS[i].first << "," << this->HIGH_OUTIE_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "COMPRESSION_AREA " << COMPRESSION_AREA << ": ";
	for(unsigned int i = 0; i < this->COMPRESSION_AREAS.size(); i++) {
		cout << "(" << this->COMPRESSION_AREAS[i].first << "," << this->COMPRESSION_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "STRECH_AREA " << STRECH_AREA << ": ";
	for(unsigned int i = 0; i < this->STRECH_AREAS.size(); i++) {
		cout << "(" << this->STRECH_AREAS[i].first << "," << this->STRECH_AREAS[i].second << ") ";
	}
	cout << "\n";

	cout << "TOTAL " << TOTAL << "\n";




	cout << "-----\n";
}



