#pragma once

#include <Processors/ISource.h>


namespace DB
{

class ReadBuffer;

/** Input format is a source, that reads data from ReadBuffer.
  */
class IInputFormat : public ISource
{
protected:

    /// Skip GCC warning: ‘maybe_unused’ attribute ignored
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

    ReadBuffer & in [[maybe_unused]];

#pragma GCC diagnostic pop

public:
    IInputFormat(Block header, ReadBuffer & in_);

    /** In some usecase (hello Kafka) we need to read a lot of tiny streams in exactly the same format.
     * The recreating of parser for each small stream takes too long, so we introduce a method
     * resetParser() which allow to reset the state of parser to continure reading of
     * source stream w/o recreating that.
     * That should be called after current buffer was fully read.
     */
    virtual void resetParser();

    virtual const BlockMissingValues & getMissingValues() const
    {
        static const BlockMissingValues none;
        return none;
    }
};

}
