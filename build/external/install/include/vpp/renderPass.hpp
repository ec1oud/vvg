#pragma once

#include <vpp/fwd.hpp>
#include <vpp/resource.hpp>

#include <vector>

namespace vpp
{

///Vulkan Renderpass. Can be created just from a vulkan device.
///Stores its description information.
class RenderPass : public Resource
{
public:
	RenderPass() = default;
	RenderPass(const Device& dev, const vk::RenderPassCreateInfo& info);
	RenderPass(const Device& dev, vk::RenderPass pass, const vk::RenderPassCreateInfo& info);
	~RenderPass();

	RenderPass(RenderPass&& other) noexcept;
	RenderPass& operator=(RenderPass other) noexcept;

	const std::vector<vk::AttachmentDescription>& attachments() const { return attachments_; }
	const std::vector<vk::SubpassDependency>& dependencies() const { return dependencies_; }
	const std::vector<vk::SubpassDescription>& subpasses() const { return subpasses_; }
	const std::vector<vk::AttachmentReference>& references() const { return references_; }

	vk::RenderPass vkRenderPass() const { return renderPass_; }

	operator vk::RenderPass() const { return vkRenderPass(); }
	friend void swap(RenderPass& a, RenderPass& b) noexcept;

protected:
	vk::RenderPass renderPass_ {};

	std::vector<vk::AttachmentDescription> attachments_;
	std::vector<vk::SubpassDescription> subpasses_;
	std::vector<vk::SubpassDependency> dependencies_;
	std::vector<vk::AttachmentReference> references_;
};

//XXX: class at the moment not useful, can later be used for addtional features/checks
///Vulkan RenderPass Instance, i.e. a commandbuffer recording session during a render pass.
class RenderPassInstance : public NonCopyable
{
protected:
	vk::RenderPass renderPass_ {};
	vk::CommandBuffer commandBuffer_ {};
	vk::Framebuffer framebuffer_ {};

public:
	RenderPassInstance(vk::CommandBuffer cmdbuf, vk::RenderPass pass, vk::Framebuffer framebuffer);
	~RenderPassInstance();

	const vk::RenderPass& renderPass() const { return renderPass_; }
	const vk::CommandBuffer& vkCommandBuffer() const { return commandBuffer_; }
	const vk::Framebuffer& vkFramebuffer() const { return framebuffer_; }
};

}
