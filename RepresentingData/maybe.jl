immutable Maybe{T}
	value::T
	isna::Bool
end

julia> Maybe(4, true)
Maybe{Int64}(4,true)

julia> Maybe(4, false)
Maybe{Int64}(4,false)