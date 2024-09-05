#include <Processors/QueryPlan/LimitByStep.h>
#include <Processors/QueryPlan/QueryPlanStepRegistry.h>
#include <Processors/Transforms/LimitByTransform.h>
#include <QueryPipeline/QueryPipelineBuilder.h>
#include <IO/Operators.h>
#include <Common/JSONBuilder.h>

namespace DB
{

static ITransformingStep::Traits getTraits()
{
    return ITransformingStep::Traits
    {
        {
            .returns_single_stream = true,
            .preserves_number_of_streams = false,
            .preserves_sorting = true,
        },
        {
            .preserves_number_of_rows = false,
        }
    };
}

LimitByStep::LimitByStep(
    const DataStream & input_stream_,
    size_t group_length_, size_t group_offset_, Names columns_)
    : ITransformingStep(input_stream_, input_stream_.header, getTraits())
    , group_length(group_length_)
    , group_offset(group_offset_)
    , columns(std::move(columns_))
{
}


void LimitByStep::transformPipeline(QueryPipelineBuilder & pipeline, const BuildQueryPipelineSettings &)
{
    pipeline.resize(1);

    pipeline.addSimpleTransform([&](const Block & header, QueryPipelineBuilder::StreamType stream_type) -> ProcessorPtr
    {
        if (stream_type != QueryPipelineBuilder::StreamType::Main)
            return nullptr;

        return std::make_shared<LimitByTransform>(header, group_length, group_offset, columns);
    });
}

void LimitByStep::describeActions(FormatSettings & settings) const
{
    String prefix(settings.offset, ' ');

    settings.out << prefix << "Columns: ";

    if (columns.empty())
        settings.out << "none\n";
    else
    {
        bool first = true;
        for (const auto & column : columns)
        {
            if (!first)
                settings.out << ", ";
            first = false;

            settings.out << column;
        }
        settings.out << '\n';
    }

    settings.out << prefix << "Length " << group_length << '\n';
    settings.out << prefix << "Offset " << group_offset << '\n';
}

void LimitByStep::describeActions(JSONBuilder::JSONMap & map) const
{
    auto columns_array = std::make_unique<JSONBuilder::JSONArray>();
    for (const auto & column : columns)
        columns_array->add(column);

    map.add("Columns", std::move(columns_array));
    map.add("Length", group_length);
    map.add("Offset", group_offset);
}

void LimitByStep::serialize(WriteBuffer & out) const
{
    writeVarUInt(group_length, out);
    writeVarUInt(group_offset, out);


    writeVarUInt(columns.size(), out);
    for (const auto & column : columns)
        writeStringBinary(column, out);
}

std::unique_ptr<IQueryPlanStep> LimitByStep::deserialize(
    ReadBuffer & in, const DataStreams & input_streams_, const DataStream *, QueryPlanSerializationSettings &)
{
    UInt64 group_length;
    UInt64 group_offset;

    readVarUInt(group_length, in);
    readVarUInt(group_offset, in);

    UInt64 num_columns;
    readVarUInt(num_columns, in);
    Names columns(num_columns);
    for (auto & column : columns)
        readStringBinary(column, in);

    return std::make_unique<LimitByStep>(input_streams_.front(), group_length, group_offset, std::move(columns));
}

void registerLimitByStep(QueryPlanStepRegistry & registry)
{
    registry.registerStep("LimitBy", LimitByStep::deserialize);
}

}
