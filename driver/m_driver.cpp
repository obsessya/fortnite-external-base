#ifndef DRIVER_CPP
#define DRIVER_CPP
#include "m_defines.hpp"

const bool driver::drive::device_io_control(void* data, requests code)
{
	if (!data || !code)
		return false;

	IO_STATUS_BLOCK block;
	invoke_data request{ 0 };

	request.unique = requests::invoke_unique;
	request.data = data;
	request.code = code;

	return direct_device_control(m_handle, nullptr, nullptr, nullptr, &block, 0, &request, sizeof(request), &request, sizeof(request));
}

const bool driver::drive::init()
{
	m_handle = CreateFileA(device_name, GENERIC_READ, 0, 0, 3, 0x00000080, 0);
	if (m_handle == INVALID_HANDLE_VALUE)
		return false;
	return true;
}

const bool driver::drive::update(int a_pid)
{
	if (!a_pid) return false;
	m_pid = a_pid;
	return true;
}

const bool driver::drive::initialize(uintptr_t image)
{
	uintptr_t ntdll_address = reinterpret_cast<uintptr_t>(GetModuleHandleA("ntdll.dll"));
	
	uintptr_t current_dtb = get_dtb(GetCurrentProcessId());
	
	uintptr_t nt_dll_physical = translate_address(ntdll_address, current_dtb);

	for (uintptr_t i = 0; i != 0x50000000; i++)
	{
		uintptr_t dtb = i << 12;

		if (dtb == current_dtb)
			continue;

		uintptr_t phys_address = translate_address(ntdll_address, dtb);
		if (!phys_address)
			continue;

		if (phys_address == nt_dll_physical)
		{
			directory_base = dtb;

			if (read<char>(image) == 0x4D)
			{
				directory_base = dtb;
				break;
			}
		}
	}

	FreeLibrary(reinterpret_cast<HMODULE>(ntdll_address));
	return true;
}

const uintptr_t driver::drive::translate_address(uintptr_t virtual_address, uintptr_t directory_base)
{
	translate_invoke data{ 0 };

	data.virtual_address = virtual_address;
	data.directory_base = directory_base;
	data.physical_address = nullptr;

	device_io_control(&data, invoke_translate);
	return reinterpret_cast<uintptr_t>(data.physical_address);
}

const uintptr_t driver::drive::get_dtb(uint32_t pid)
{
	dtb_invoke data{ 0 };

	data.pid = pid; 
	data.dtb = 0;

	device_io_control(&data, invoke_dtb);
	return data.dtb;
}

const uintptr_t driver::drive::get_image_base()
{
	base_invoke data{ 0 };

	data.pid = m_pid;
	data.handle = 0;
	//data.name = module_name;

	device_io_control(&data, invoke_base);
	/*std::cout << "base -> " << data.handle << std::endl;*/
	return data.handle;
}

const uintptr_t driver::drive::get_process_context()
{
	context_invoke data{ 0 };

	data.pid = m_pid;
	data.context = nullptr;

	device_io_control(&data, invoke_context);
	return reinterpret_cast<uintptr_t>(data.context);
}

const bool driver::drive::read_physical(const uintptr_t address, void* buffer, const size_t size)
{
	read_invoke data{ 0 };

	data.pid = m_pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	return device_io_control(&data, invoke_read);
}

const bool driver::drive::write_physical(const uintptr_t address, void* buffer, const size_t size)
{
	write_invoke data{ 0 };

	data.pid = m_pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	return device_io_control(&data, invoke_write);
}

const bool driver::drive::signature_scan(const char* signature, const size_t size)
{
	scan_invoke data{ 0 };

	data.pid = m_pid;
	data.module_base = image_base;
	data.signature = signature;
	data.size = size;

	return device_io_control(&data, invoke_scan);
}

const int driver::drive::initaite_mouse_context()
{
	init_invoke data{ 0 };

	data.count = 0;

	device_io_control(&data, invoke_init);
	return data.count;
}

const int driver::drive::inject_mouse(LONG MovementX, LONG MovementY)
{
	mouse_invoke data{ 0 };

	data.pid = m_pid;
	data.IndicatorFlags = MOUSEEVENTF_MOVE;
	data.MovementX = MovementX;
	data.MovementY = MovementY;
	data.PacketsConsumed = 0;

	device_io_control(&data, invoke_mouse);
	return data.PacketsConsumed;
}

const uintptr_t driver::drive::allocate_virtual(const size_t size, int type, const DWORD protection)
{
	allocate_invoke data{ 0 };

	data.pid = m_pid;
	data.size = size;
	data.protection = protection;
	data.type = type;
	data.address = 0;

	device_io_control(&data, invoke_allocate);
	return data.address;
}

const DWORD driver::drive::protect_virtual(const uintptr_t address, const size_t size, const DWORD protection)
{
	protect_invoke data{ 0 };

	data.address = address;
	data.pid = m_pid;
	data.size = size;
	data.protection = protection;
	data.old_protection = 0;

	device_io_control(&data, invoke_protect);
	return data.old_protection;
}

const uintptr_t driver::drive::swap_virtual(const uintptr_t address, const uintptr_t address2)
{
	swap_invoke data{ 0 };

	data.address = address;
	data.address2 = address2;
	data.og_pointer = 0;
	data.pid = m_pid;

	device_io_control(&data, invoke_swap);
	return data.og_pointer;
}

void driver::drive::free_virtual(const uintptr_t address, const size_t size, const ULONG type)
{
	free_invoke data{ 0 };

	data.address = address;
	data.pid = m_pid;
	data.size = size;
	data.type = type;

	device_io_control(&data, invoke_free);
}

void driver::drive::query_virtual(uintptr_t address)
{
	query_invoke data{ 0 };

	data.pid = m_pid;
	data.address = address;
	data.mem_size = 0;
	data.protect = 0;
	data.address_2 = 0;

	device_io_control(&data, invoke_query);

	std::cout << "Address size: " << data.mem_size << std::endl;
	std::cout << "Address protection: " << data.protect << std::endl;
	std::cout << "Address read: " << data.address_2 << std::endl;
}

#endif // ! DRIVER_CPP