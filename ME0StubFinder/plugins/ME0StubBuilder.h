#ifndef GEMDigi_ME0StubBuilder_h
#define GEMDigi_ME0StubBuilder_h

/** \class ME0StubBuilder derived by ME0StubBuilder
 * Algorithm to build ME0Stub's from GEMDigi collection
 * by implementing a 'build' function required by ME0StubProducer.
 *
 * Implementation notes: <BR>
 * Configured via the Producer's ParameterSet. <BR>
 * Presume this might become an abstract base class one day. <BR>
 *
 * \author Piet Verwilligen
 *
*/

#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0StubCollection.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"


class ME0StubAlgorithmBase;

class ME0StubBuilder {
public:
  /** Configure the algorithm via ctor.
     * Receives ParameterSet percolated down from EDProducer
     * which owns this Builder.
     */
  explicit ME0StubBuilder(const edm::ParameterSet&);
  /// Destructor
  ~ME0StubBuilder();

  /** Find digis in each ensemble of 6 GEM layers, build ME0Stub's ,
     *  and fill into output collection.
     */
  void build(const GEMDigiCollection* digis, ME0StubCollection& oc);

  /** Cache pointer to geometry _for current event_
     */

  static void fillDescription(edm::ParameterSetDescription& descriptions);

private:
};

#endif
