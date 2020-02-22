#include "objects.h"
#include "code_objects/synapses_post_push_spikes.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>

void _run_synapses_post_push_spikes()
{
    using namespace brian;


    ///// CONSTANTS ///////////
    const int _num_spikespace = 2;
    ///// POINTERS ////////////
        
    int32_t* __restrict  _ptr_array_neurongroup__spikespace = _array_neurongroup__spikespace;


    //// MAIN CODE ////////////
    // we do advance at the beginning rather than at the end because it saves us making
    // a copy of the current spiking synapses
    
    {
        synapses_post.advance();
        synapses_post.push(_ptr_array_neurongroup__spikespace, _ptr_array_neurongroup__spikespace[_num_spikespace-1]);
    }

}
