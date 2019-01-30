#ifndef FINDVARIABLEVISITORTEST_H
#define FINDVARIABLEVISITORTEST_H

#include <ASTTraversal/FindVariableVisitor.h>

#include <gtest/gtest.h>


// TEST FIXTURE
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace ASTTraversal {

/*!
 *
 * src:
 *  https://github.com/abseil/googletest/blob/master/googletest/docs/primer.md
 *  https://github.com/abseil/googletest/blob/master/googletest/samples/sample3_unittest.cc
 *
 */
class cFindVariableVisitorTest :
    public testing::Test {

protected:

    cFindVariableVisitorTest();

    // testing::Test METHODS
    // ------------------------------------------------------------------------

    /*!
     *  This will be called before each test is run.
     */
    void SetUp() override;

    /*!
     *  This will be called after each test is run.
     */
    void TearDown() override;


    // VARIABLES FOR THE TESTS
    // ------------------------------------------------------------------------

    cFindVariableVisitor m_varFinderVisitor;

}; /* cFindVariableVisitorTest */

} /* ASTTraversal */

} /* TOOBAD4ML */

#endif /* FINDVARIABLEVISITORTEST_H */
