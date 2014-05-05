#ifndef __FILTER_H__
#define __FILTER_H__
#include <Picture.h>

/** @addtogroup videostream
 * @{
 */

/**
 * @class Filter
 *
 * The class is used within the VideoStream package to allow for the
 * creation of various image filters, which can be applied to a stream
 * and the results will be visible in real time.
 *
 * @brief The class defines a framework for creating data filters
 * which can manipulate images, and apply any changes in the image 
 * data back to the image.
 *
 * @author Richard Edwards and John Hoare
 */

class Filter {

    public:


    /// Default Constructor
    Filter();
    ~Filter();

    /**
     * A function for applying the filter to an image. Note,
     * one should always invoke applyFilter, and not invoke filter.
     *
     * The reasoning behind this will be more clear, when the class
     * is extended to allow for a filter to yield data from its
     * application. 
     */
    void applyFilter(PicturePtr);

    /**
     * The function used by applyFilter to actually process
     * an image. However, when developing your own filter,
     * if you do not overwrite this function, then the filter's
     * default behavior is to do nothing.
     */
    virtual void filter(PicturePtr);

};

///@}

#endif
