#ifndef Controller_hpp
#define Controller_hpp

#include "../dto/DTOs.hpp"
#include "../service/W2lService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class Controller : public oatpp::web::server::api::ApiController
{
private:
    W2lService m_w2lService;

public:
    Controller(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }

public:
    ENDPOINT("GET", "/", root)
    {
        auto dto = SttResponseDto::createShared();
        dto->statusCode = 200;
        dto->message = "OK";
        dto->text = "-";
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(stt)
    {
        info->summary = "STT";

        info->addConsumes<Object<SttRequestDto>>("application/json");

        info->addResponse<Object<SttResponseDto>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", "/stt", stt, BODY_DTO(Object<SttRequestDto>, requestDto))
    {
        auto fileName = requestDto->fileName;
        if (!fileName)
        {
            auto dto = SttResponseDto::createShared();
            dto->statusCode = 400;
            dto->message = "fileName must be provided";
            return createDtoResponse(Status::CODE_400, dto);
        }

        auto text = m_w2lService.m_w2lHelper->audioFileToText(fileName->std_str());

        auto dto = SttResponseDto::createShared();
        dto->statusCode = 200;
        dto->message = "OK";
        dto->text = oatpp::String(text.c_str());

        return createDtoResponse(Status::CODE_200, dto);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* Controller_hpp */
