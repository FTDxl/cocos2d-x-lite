#include "CoreStd.h"
#include "GFXInputAssembler.h"

namespace cc {

GFXInputAssembler::GFXInputAssembler(GFXDevice *device)
: GFXObject(GFXObjectType::INPUT_ASSEMBLER), _device(device) {
}

GFXInputAssembler::~GFXInputAssembler() {
}

void GFXInputAssembler::extractDrawInfo(GFXDrawInfo &drawInfo) const {
    drawInfo.vertexCount = _vertexCount;
    drawInfo.firstVertex = _firstVertex;
    drawInfo.indexCount = _indexCount;
    drawInfo.firstIndex = _firstIndex;
    drawInfo.vertexOffset = _vertexOffset;
    drawInfo.instanceCount = _instanceCount;
    drawInfo.firstInstance = _firstInstance;
}

uint GFXInputAssembler::computeAttributesHash() const {
    // https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
    // 6: GFXAttribute has 6 elements.
    std::size_t seed = _attributes.size() * 6;
    for (const auto attribute : _attributes) {
        seed ^= std::hash<std::string>{}(attribute.name) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= (uint)(attribute.format) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= attribute.isNormalized + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= attribute.stream + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= attribute.isInstanced + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= attribute.location + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

}
