#pragma once

#include <vpp/fwd.hpp>
#include <vpp/resource.hpp>
#include <vpp/buffer.hpp>
#include <vpp/utility/allocation.hpp>

#include <memory>
#include <mutex>

namespace vpp
{

///Provides transfer buffers to easily fill large device local buffers and images.
///Basically a pool of mappable vulkan buffers, which can be used for copying.
///Can be used by multiple threads at the same time.
class TransferManager : public Resource
{
protected:
	class TransferBuffer;

public:
	///Represents a part of a transfer buffer which can be used for transerfering data to the gpu.
	///The destructor does automatically release the used transfer buffer range.
	class BufferRange : public ResourceReference<BufferRange>
	{
	public:
		BufferRange() = default;
		BufferRange(TransferBuffer& buf, const Allocation& al) : buffer_(&buf), allocation_(al) {}
		~BufferRange();

		BufferRange(BufferRange&& other) noexcept;
		BufferRange& operator=(BufferRange other) noexcept;

		const Buffer& buffer() const { return buffer_->buffer(); }
		vk::Buffer vkBuffer() const { return buffer().vkBuffer(); }
		const Allocation& allocation() const { return allocation_; }
		std::size_t offset() const { return allocation().offset; }
		std::size_t size() const { return allocation().size; }

		const TransferBuffer& resourceRef() const { return *buffer_; }
		friend void swap(BufferRange& a, BufferRange& b) noexcept;

	protected:
		TransferBuffer* buffer_ {};
		Allocation allocation_ {};
	};

public:
	TransferManager() = default;
	TransferManager(const Device& dev);

	///Returns an avaible upload buffer with the given size (allocates one if not already there).
	BufferRange buffer(std::size_t size);

	///Returns the amount of vulkan buffers managed.
	std::size_t bufferCount() const { return buffers_.size(); }

	///Returns the total buffer size of all owned buffers.
	std::size_t totalSize() const;

	///Returns the amount of currently for transerfing used ranges.
	std::size_t activeRanges() const;

	///Additionally reserves the amount of transfer buffer capacity
	void reserve(std::size_t size);

	///Releases all currently unused buffers.
	void shrink();

	///Optimizes the memory allocation. Will recreate all unused buffers as one big buffer.
	void optimize();

protected:
	class TransferBuffer : ResourceReference<TransferBuffer>
	{
	public:
		TransferBuffer(const Device& dev, std::size_t size, std::mutex& mtx);
		~TransferBuffer();

		const Buffer& buffer() const { return buffer_; }

		Allocation use(std::size_t size);
		bool release(const Allocation& alloc);
		std::size_t rangesCount() const { return ranges_.size(); }

		const Buffer& resourceRef() const { return buffer_; }

	protected:
		Buffer buffer_;
		std::vector<Allocation> ranges_;
		std::mutex& mutex_;
	};

protected:
	//transfer buffer pool
	//must be a pointer for the BufferRange pointer member to stay valid.
	std::vector<std::unique_ptr<TransferBuffer>> buffers_;
	mutable std::mutex mutex_;
};

///Convinient typedef for TransferManager::BufferRange
using TransferRange = TransferManager::BufferRange;

}
