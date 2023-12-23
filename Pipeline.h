
#ifndef OVKL_PIPELINE_H
#define OVKL_PIPELINE_H

#include <vector>
#include <stdexcept>

#include "common.h"

class Pipeline {
public:
    VkPipeline buildPipeline(VkDevice device, VkRenderPass pass);

    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    VkPipelineVertexInputStateCreateInfo vertexInputInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineMultisampleStateCreateInfo multisampling;
    VkPipelineLayout pipelineLayout;

    VkPipelineShaderStageCreateInfo pipelineShaderStageCreation(VkShaderStageFlagBits stage, VkShaderModule shaderModule);
    VkPipelineVertexInputStateCreateInfo vertexInputStateCreation();
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreation(VkPrimitiveTopology topology);
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreation(VkPolygonMode polygonMode);
    VkPipelineMultisampleStateCreateInfo  multisampleStateCreation();
    VkPipelineColorBlendAttachmentState colorBlendAttachmentStateCreation();
};


#endif //OVKL_PIPELINE_H
